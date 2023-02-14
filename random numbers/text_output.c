#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");
    unsigned char plaintext[100][100], key[100], ciphertext[100][100], decrypted[100][100];
    int key_len = 100;
    int i, j;
    
    // Read plaintext values from input file
    for (i = 0; i < 100; i++) {
        fgets(plaintext[i], 100, input_file);
        plaintext[i][strcspn(plaintext[i], "\n")] = 0;  // remove trailing newline
    }
    fclose(input_file);
    
    // Generate key
    generate_key(key, key_len);
    
    // Encrypt each plaintext value and write results to output file
    for (i = 0; i < 100; i++) {
        encrypt(plaintext[i], strlen(plaintext[i]), key, key_len, ciphertext[i]);
        decrypt(ciphertext[i], strlen(plaintext[i]), key, key_len, decrypted[i]);
        fprintf(output_file, "Plaintext: %s\n", plaintext[i]);
        fprintf(output_file, "Ciphertext: %s\n", ciphertext[i]);
        fprintf(output_file, "Decrypted text: %s\n\n", decrypted[i]);
    }
    
    fclose(output_file);
    
    return 0;
}
