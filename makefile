all:
	gcc openssl_test.c -g -o test -lssl -lcrypto -w
	gcc rc4_test.c -g -o rc4_test -lssl -lcrypto -w
	./rc4_test
