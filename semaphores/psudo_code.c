// Initialization
semaphore key = 1; // Initialize key semaphore to 1

// Encryption function
encrypt(message)
  P(key) // Acquire key semaphore
  for i = 1 to length(message)
    message[i] = message[i] + ENCRYPTION_KEY // Add fixed value to ASCII code
  end for
  V(key) // Release key semaphore

// Decryption function
decrypt(message)
  P(key) // Acquire key semaphore
  for i = 1 to length(message)
    message[i] = message[i] - ENCRYPTION_KEY // Subtract fixed value from ASCII code
  end for
  V(key) // Release key semaphore

// Main program
message = input() // Get message from user
encrypt(message)
print("Encrypted message: ", message)
decrypt(message)
print("Decrypted message: ", message)
