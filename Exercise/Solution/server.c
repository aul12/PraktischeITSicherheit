#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

#include <sgx.h>
#include <sgx-user.h>
#include <sgx-kern.h>
#include <sgx-lib.h>

#include "libpipe.h"

int votes[256];
bool voted_already[256];

char *handle_vote(int in_fd, int out_fd) {
	char buf[2];
	size_t readed = 0;
	do {
		ssize_t res = read(in_fd, buf, 2-readed);
		if (res < 0) {
			fprintf(stderr, "Invalid response by read: %s", strerror(errno));
			return "An error occured, please try again!";
		}
		readed += res;
	} while (readed < 2);	
	uint8_t id = buf[0];
	uint8_t vote = buf[1];
	
	if (voted_already[id]) {
		return "You voted already!";
	}

	votes[vote] += 1;
	voted_already[id] = true;	

	return "Vote succesfully!";
}

/* main operation. communicate with tor-gencert & tor process */
void enclave_main(int argc, char **argv)
{
	for (int c=0; c<256; ++c) {
		votes[c] = 0;
		voted_already[c] = false;
	}

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
		int ret = sgx_intra_attest_target(8024);
		char *response;
		if(ret == 1) {
			response = handle_vote(fd_ae, fd_ea);
		} else {
			response = "Intra Attestation Fail!";
		}
		write(fd_ea, response, strlen(response)+1);
	}

	// Print winner
	int argmax = 0;
	for (int c=1; c<256; ++c) {
		if (votes[c] > votes[argmax]) {
			argmax = c;
		}
	}
	printf("Winner: %d\n", argmax);	

	close(fd_ea);
	close(fd_ae);
}
