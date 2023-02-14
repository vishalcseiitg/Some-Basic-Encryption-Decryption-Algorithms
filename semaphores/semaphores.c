#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

#define BUFFER_SIZE 1024
#define ENCRYPTION_KEY 3

sem_t key; // Semaphore for key

void encrypt(char* message) {
  sem_wait(&key); // Acquire key semaphore
  for (int i = 0; i < strlen(message); i++) {
    message[i] += ENCRYPTION_KEY; // Add fixed value to ASCII code
  }
  sem_post(&key); // Release key semaphore
}

void decrypt(char* message) {
  sem_wait(&key); // Acquire key semaphore
  for (int i = 0; i < strlen(message); i++) {
    message[i] -= ENCRYPTION_KEY; // Subtract fixed value from ASCII code
  }
  sem_post(&key); // Release key semaphore
}

int main() {
  char message[BUFFER_SIZE];
  
  sem_init(&key, 0, 1); // Initialize key semaphore to 1
  
  // Get message from user
  printf("Enter a message to encrypt: ");
  fgets(message, BUFFER_SIZE, stdin);
  message[strcspn(message, "\n")] = '\0'; // Remove newline character
  
  encrypt(message);
  printf("Encrypted message: %s\n", message);
  
  decrypt(message);
  printf("Decrypted message: %s\n", message);
  
  sem_destroy(&key); // Destroy key semaphore
  return 0;
}
