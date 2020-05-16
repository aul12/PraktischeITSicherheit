#include <sgx-lib.h>
#include <stdio.h>

void enclave_main() {
	printf("Hello World!\n");
	sgx_exit(NULL);
}
