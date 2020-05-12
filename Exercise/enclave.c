#include <assert.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sgx.h>
#include <sgx-user.h>
#include <sgx-kern.h>
#include <sgx-lib.h>

#include "libpipe.h"


// For simplicity, this function do simple operation.
// In the realistic scenario, key creation, signature generation and etc will be
// the possible example.
void do_secret(char *buf) 
{
	for(int i=0; i<strlen(buf); i++) {
		buf[i]++;
	}
}

/* main operation. communicate with tor-gencert & tor process */
void enclave_main(int argc, char **argv)
{
	int fd_ea = -1;
	int fd_ae = -1;

	char *port_enc_to_app = "e2a";
	char *port_app_to_enc = "a2e";

	if(pipe_init(0) < 0) {
		puts("Error in pipe_init");
		sgx_exit(NULL);
	}

	if((fd_ea = pipe_open(port_enc_to_app, RB_MODE_WR, 0)) < 0) {
		puts("Error in pipe_open");
		sgx_exit(NULL);
	}

	if((fd_ae = pipe_open(port_app_to_enc, RB_MODE_RD, 0)) < 0) {
		puts("Error in pipe_open");
		sgx_exit(NULL);
	}

	// Read the request operations
	int len;
	char msg[20];
	char tmp_buf[20];

	read(fd_ae, &len, sizeof(int));
	read(fd_ae, msg, len+1);

	if(!strncmp(msg, "Do Something", len)) {
		// Here, secure operation should be executed.
		read(fd_ae, tmp_buf, 20);
		do_secret(tmp_buf);
	}

	// Send the result
	write(fd_ea, tmp_buf, 20);       

	close(fd_ea);
	close(fd_ae);
}
