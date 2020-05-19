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
    int target_port, ret;
    char *conf = "/home/sgx/PraktischeITSicherheit/Exercise/Solution/server.conf";
    target_port = 8024;

    ret = sgx_intra_attest_challenger(target_port, conf);
    if(ret == 1) {
        puts("Intra Attestaion Success!");
    } else {
        puts("Intra Attestation Fail!");
    }
    
    sgx_exit(NULL);
}
