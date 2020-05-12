#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libpipe.h"


int main(int argc, char *argv[]) 
{
	// Get votes
	unsigned uid;
	unsigned vote;
	printf("Please enter your identifier:\n");
	scanf("%u", &uid);
	printf("Select your vote:\n");
	scanf("%u", &vote);
	printf("%u, %u\n", uid, vote);

	// Initialize and open pipes
	int fd_ea = -1;
	int fd_ae = -1;

	char *port_enc_to_app = "e2a";
	char *port_app_to_enc = "a2e";

	if (pipe_init(0) < 0) {
		perror("Error in pipe_init");
		exit(1);
	}

	if ((fd_ea = pipe_open(port_enc_to_app, RB_MODE_RD, 0)) < 0) {
		perror("Error in pipe_open");
		exit(1);
	}

	if ((fd_ae = pipe_open(port_app_to_enc, RB_MODE_WR, 0)) < 0) {
		perror("Error in pipe_open");
		exit(1);
	}

	char buf[2] = {(char)uid, (char)vote};
	write(fd_ae, buf, sizeof(buf));

	char response[128];
	read(fd_ea, response, sizeof(response));
	printf("Response: %s", response);

	close(fd_ae);
	close(fd_ea);
	
	// Request some operations
	/*int len;
	len = strlen("Do Something");
	write(fd_ae, &len, sizeof(int));
	write(fd_ae, "Do Something", len+1);

	// Send input
	char tmp_buf[20];
	strcpy(tmp_buf, "11111111");
	write(fd_ae, tmp_buf, 20);
	printf("Input = %s\n", tmp_buf);

	// Receive the result
	read(fd_ea, tmp_buf, 20); 
	printf("Output = %s\n", tmp_buf);*/

	return 0;
}
