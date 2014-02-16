all:
	gcc openssl_test.c -g -o test -lssl -lcrypto
	./test
