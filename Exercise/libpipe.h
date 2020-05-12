#ifndef LIBPIPE_H
#define LIBPIPE_H

#define RB_MODE_RD 0
#define RB_MODE_WR 1

int pipe_init(int flag_dir);

int pipe_open(char *unique_id, int is_write, int flag_dir);

#endif
