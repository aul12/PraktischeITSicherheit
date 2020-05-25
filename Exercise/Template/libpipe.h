#ifndef LIBPIPE_H
#define LIBPIPE_H

/**
 * Initialize the library by creating the required temporary directories.
 * Call this function once at in the beginning.
 */
int pipe_init(void);

/**
 * Open a pipe, can be used for both reading and writing.
 * @param unique_id a (null terminated) string containing the name for your pipe
 * @return a file descriptor that can be used for read/write syscalls
 */
int pipe_open(char *unique_id);

#endif
