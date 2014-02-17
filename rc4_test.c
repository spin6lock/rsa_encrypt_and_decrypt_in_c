#include <stdio.h>
#include <openssl/rc4.h>

int main() {
    const unsigned char key_text[] = "Frozen";
    unsigned char plaintext[] = "Hello world\n";
    unsigned char crypted_text[sizeof(plaintext)] = {0};
    int plaintext_size = sizeof(plaintext) - 1;
    RC4_KEY key;
    RC4_set_key(&key, sizeof(key_text) - 1, key_text);
    RC4(&key, plaintext_size, plaintext, crypted_text);
    for (int i = 0; i < sizeof(plaintext); i++) {
        printf("\\x%02x", crypted_text[i]);
    }
    printf("\bdecrypted\n");
    RC4_set_key(&key, sizeof(key_text) - 1, key_text);
    RC4(&key, plaintext_size, crypted_text, plaintext);
    for (int i = 0; i < sizeof(plaintext); i++) {
        printf("\\x%02x", plaintext[i]);
    }
    printf("\nin text\n%s", plaintext);
    return 0;
}
