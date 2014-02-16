#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdio.h>

int main() {
    const unsigned char text[] = "hello world";
    unsigned char crypt_text[1024];
    unsigned char decrypt_text[1024 - 11];
    RSA *public_key = NULL;
    RSA *private_key = NULL;
    public_key = RSA_new();
    private_key = RSA_new();
    FILE *fpub = fopen("public_key", "r");
    FILE *fpriv = fopen("private_key", "r");
    printf("text: %s\n", text);
    RSA *ret = PEM_read_RSA_PUBKEY(fpub, &public_key, NULL, NULL);
    printf("pubkey ret: %d\n", ret);
    ret = PEM_read_RSAPrivateKey(fpriv, &private_key, NULL, NULL);
    printf("prikey ret: %d\n", ret);

    //私钥加密，公钥解密
    int num = RSA_private_encrypt(sizeof(text) - 1, text, crypt_text, 
            private_key, RSA_PKCS1_PADDING);
    printf("num: %d\n", num); 
    for (int i = 0; i < num; i++) {
        printf("\\x%02x", crypt_text[i]);
    }

    printf("\ndecrypt\n");
    int decrypt_len = RSA_public_decrypt(num, crypt_text, decrypt_text,
            public_key, RSA_PKCS1_PADDING);
    if (decrypt_len < 0) printf("error: %lu\n", ERR_get_error());
    printf("decrypt_len: %d\n", decrypt_len);
    printf("decrypt text: %s\n", decrypt_text);

    //公钥加密，私钥解密
    num = RSA_public_encrypt(sizeof(text) - 1, text, crypt_text, 
            public_key, RSA_PKCS1_PADDING);
    printf("num: %d\n", num); 
    for (int i = 0; i < num; i++) {
        printf("\\x%02x", crypt_text[i]);
    }

    printf("\ndecrypt\n");
    decrypt_len = RSA_private_decrypt(RSA_size(private_key), crypt_text,
            decrypt_text, private_key, RSA_PKCS1_PADDING);
    if (decrypt_len < 0) printf("error: %lu\n", ERR_get_error());
    printf("decrypt_len: %d\n", decrypt_len);
    printf("decrypt text: %s\n", decrypt_text);

    return 0;
}
