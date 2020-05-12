#include <sgx-lib.h>
#include <stdio.h>

void enclave_main() {
	printf("HelloWorld!\n");
	sgx_exit(NULL);
}
