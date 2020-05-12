/*
 *  Copyright (C) 2015, OpenSGX team, Georgia Tech & KAIST, All Rights Reserved
 *
 *  This file is part of OpenSGX (https://github.com/sslab-gatech/opensgx).
 *
 *  OpenSGX is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  OpenSGX is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with OpenSGX.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libpipe.h"


int main(int argc, char *argv[]) 
{
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

	// Request some operations
	int len;
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
	printf("Output = %s\n", tmp_buf);

	return 0;
}
