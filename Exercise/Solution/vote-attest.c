#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sgx.h>
#include <sgx-user.h>
#include <sgx-kern.h>
#include <sgx-lib.h>

#include "libpipe.h"

void enclave_main()
{
	// Get votes
	unsigned uid;
	unsigned vote;
	printf("Please enter your identifier:\n");
	scanf("%u", &uid);
	printf("Select your vote:\n");
	scanf("%u", &vote);
	printf("You (%u) will vote for: %u\n", uid, vote);

	// Initialize and open pipes
	int fd_ea = -1;
	int fd_ae = -1;

	char *port_enc_to_app = "e2a";
	char *port_app_to_enc = "a2e";

	if (pipe_init() < 0) {
		perror("Error in pipe_init");
		exit(1);
	}

	if ((fd_ea = pipe_open(port_enc_to_app, RB_MODE_RD)) < 0) {
		perror("Error in pipe_open");
		exit(1);
	}

	if ((fd_ae = pipe_open(port_app_to_enc, RB_MODE_WR)) < 0) {
		perror("Error in pipe_open");
		exit(1);
	}

	// Run attestation
	int target_port, ret;
	char *conf = "/home/sgx/PraktischeITSicherheit/Exercise/Solution/server.conf";
	target_port = 8024;

	ret = sgx_intra_attest_challenger(target_port, conf);
	if(ret == 1) {
		printf("Intra Attestaion Success!\n");
		// Send vote and wait for response
		char buf[2] = {(char)uid, (char)vote};
		write(fd_ae, buf, sizeof(buf));
	} else {
		printf("Intra Attestation Fail!\n");
	}
	char response[128];
	read(fd_ea, response, sizeof(response));
	printf("Response: %s\n", response);

	close(fd_ae);
	close(fd_ea);

	sgx_exit(NULL);
}
