#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <fcntl.h>
#include <err.h>
#include <assert.h>

#include <sys/stat.h>

#include <sgx.h>
#include <sgx-user.h>
#include <sgx-kern.h>
#include <sgx-lib.h>

#define is_aligned(addr, bytes) \
	((((uintptr_t)(const void *)(addr)) & (bytes - 1)) == 0)

void enclave_main()
{
	// Your code here
	sgx_exit(NULL);
}
