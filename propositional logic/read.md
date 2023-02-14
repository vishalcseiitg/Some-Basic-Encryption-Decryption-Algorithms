An encryption-decryption algorithm using the concepts of propositional logic could be based on the principles of Boolean logic and Boolean functions. Here's an outline of one such algorithm:

1. Represent the message as a series of binary digits.
2. Choose a Boolean function that takes two input variables and produces an output variable. This function should be easily invertible.
3. Choose two sets of Boolean values, one to use as the key and one to use as the encryption key.
4. For each bit in the message, use the Boolean function to encrypt the bit using one of the values from the encryption key and one of the values from the key.
5. The encrypted message is the series of encrypted bits.
6. To decrypt the message, simply invert the Boolean function and apply it to the encrypted bits, using the key.
