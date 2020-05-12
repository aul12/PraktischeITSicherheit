#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sgx.h>
#include <sgx-user.h>
#include <sgx-kern.h>
#include <sgx-lib.h>

#include "libpipe.h"

void handle_vote(int in_fd, int out_fd) {
	char buf[2];
	size_t readed = 0;
	do {
		ssize_t res = read(in_fd, buf, 2-readed);
		if (res < 0) {
			fprintf(stderr, "Invalid response by read: %s", strerror(errno));
			return;
		}
		readed += res;
	} while (readed < 2);	
	uint8_t id = buf[0];
	uint8_t vote = buf[1];

	printf("%d voted for %d\n", id, vote);
	char response[] = "Vote succesfull!";
	write(out_fd, response, strlen(response)+1);
}

/* main operation. communicate with tor-gencert & tor process */
void enclave_main(int argc, char **argv)
{
	// Setup pipe
	int fd_ea = -1;
	int fd_ae = -1;

	char *port_enc_to_app = "e2a";
	char *port_app_to_enc = "a2e";

	if(pipe_init() < 0) {
		puts("Error in pipe_init");
		sgx_exit(NULL);
	}

	if((fd_ea = pipe_open(port_enc_to_app, RB_MODE_WR)) < 0) {
		puts("Error in pipe_open");
		sgx_exit(NULL);
	}

	if((fd_ae = pipe_open(port_app_to_enc, RB_MODE_RD)) < 0) {
		puts("Error in pipe_open");
		sgx_exit(NULL);
	}

	// Wait for three votes
	for (int c=0; c<3; ++c) {
		handle_vote(fd_ae, fd_ea);
	}

	close(fd_ea);
	close(fd_ae);
}
