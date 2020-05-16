#include "libpipe.h"

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

const char TMP_DIRECTORY_CONF[] = "/tmp/ipc_conf";
const char TMP_DIRECTORY_RUN[] = "/tmp/ipc_run";
const char TMP_FILE_NUMBER_FMT[] =  "/pipe_";
const int NAME_BUF_SIZE = 256;

int pipe_init(void)
{
	int ret = mkdir(TMP_DIRECTORY_CONF, 0770);

	if(ret == -1) {
		if(errno != EEXIST) {
			puts("Fail to mkdir");
			return -1;
		}
	}
	return 0;
}

int pipe_open(char *unique_id, int is_write)
{
	char name_buf[NAME_BUF_SIZE];

	strcpy(name_buf, TMP_DIRECTORY_CONF);
	strcpy(name_buf+strlen(name_buf), TMP_FILE_NUMBER_FMT);
	strcpy(name_buf+strlen(name_buf), unique_id);

	int ret = mknod(name_buf, S_IFIFO | 0770, 0);
	if (ret == -1) {
		if(errno != EEXIST) {
			puts("Fail to mknod");
			return -1;
		}
	}

	int flag = O_ASYNC;
	if(is_write) {
		flag |= O_WRONLY;
	} else {
		flag |= O_RDONLY;
	}

	int fd = open(name_buf, flag);

	if (fd == -1) {
		puts("Fail to open");
		return -1;
	}

	return fd;
}

