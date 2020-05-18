OPENSGX=$(OPENSGX_DIR)/opensgx
ROOT=$(PWD)

%.enc: %.sgx %.conf
	cd $(OPENSGX_DIR); $(OPENSGX) -i $(addprefix $(ROOT)/, $+)

%.run: %.out
	./$<

%.out: %.c libpipe.c
	cc $^ -o $@


%.conf: %.sgx %.key
	$(OPENSGX) -s $< --key $*.key

%.sgx: %.o libpipe.o
	cc -static -nostdlib -nostartfiles -Wl,-T,$(OPENSGX_DIR)/user/sgx.lds $^ -o $@ $(OPENSGX_DIR)/libsgx/sgx-entry.o $(OPENSGX_DIR)/libsgx/libsgx.a $(OPENSGX_DIR)/libsgx/libpolarssl-sgx.a $(OPENSGX_DIR)/libsgx/libc-sgx.a

%.o: %.c
	cc -c -g -I$(OPENSGX_DIR)/user/include -I$(OPENSGX_DIR)/user/share/include -Wall -pedantic -Wno-unused-function -std=gnu11 -I$(OPENSGX_DIR)/libsgx/include -I$(OPENSGX_DIR)/libsgx/musl-libc/include -fno-stack-protector -static -fvisibility=hidden -o $@ $<

%.key:
	$(OPENSGX) -k
	mv sign.key $@

clean:
	rm -f sign.key
	rm -f *.sgx
	rm -f *.conf
	rm -f *.out
	rm -f *.o
