#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 8

void generate_key(unsigned char *key, int key_len) {
    int i;
    for (i = 0; i < key_len; i++) {
        key[i] = (unsigned char) rand();
    }
}

void encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, int key_len, unsigned char *ciphertext) {
    int i, j;
    unsigned char block[BLOCK_SIZE], rand_seq[BLOCK_SIZE];
    for (i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        // Generate random sequence
        generate_key(rand_seq, BLOCK_SIZE);
        // XOR with key to get new sequence
        for (j = 0; j < BLOCK_SIZE && i+j < plaintext_len; j++) {
            rand_seq[j] ^= key[(i+j) % key_len];
        }
        // XOR plaintext block with new sequence
        for (j = 0; j < BLOCK_SIZE && i+j < plaintext_len; j++) {
            block[j] = plaintext[i+j] ^ rand_seq[j];
        }
        // Copy result to ciphertext
        for (j = 0; j < BLOCK_SIZE && i+j < plaintext_len; j++) {
            ciphertext[i+j] = block[j];
        }
    }
}

void decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, int key_len, unsigned char *plaintext) {
    int i, j;
    unsigned char block[BLOCK_SIZE], rand_seq[BLOCK_SIZE];
    for (i = 0; i < ciphertext_len; i += BLOCK_SIZE) {
        // Generate random sequence
        generate_key(rand_seq, BLOCK_SIZE);
        // XOR with key to get new sequence
        for (j = 0; j < BLOCK_SIZE && i+j < ciphertext_len; j++) {
            rand_seq[j] ^= key[(i+j) % key_len];
        }
        // XOR ciphertext block with new sequence
        for (j = 0; j < BLOCK_SIZE && i+j < ciphertext_len; j++) {
            block[j] = ciphertext[i+j] ^ rand_seq[j];
        }
        // Copy result to plaintext
        for (j = 0; j < BLOCK_SIZE && i+j < ciphertext_len; j++) {
            plaintext[i+j] = block[j];
        }
    }
}

int main() {
    unsigned char plaintext[] = "Hello, world!";
    int plaintext_len = sizeof(plaintext) - 1;
    unsigned char key[plaintext_len], ciphertext[plaintext_len], decrypted[plaintext_len];
    int key_len = plaintext_len;
    
    // Generate key
    generate_key(key, key_len);
    
    // Encrypt plaintext
    encrypt(plaintext, plaintext_len, key, key_len, ciphertext);
    
    // Decrypt ciphertext
    decrypt(ciphertext, plaintext_len, key, key_len, decrypted);
    
    // Print results
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < plaintext_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted: %s\n", decrypted);
    
    return 0;
}
