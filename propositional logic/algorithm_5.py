def xor(a, b):
    return a != b

def encrypt(message, key1, key2):
    encrypted_message = []
    for m in message:
        encrypted_message.append(xor(m, key1) ^ xor(m, key2))
    return encrypted_message

def decrypt(encrypted_message, key1, key2):
    decrypted_message = []
    for em in encrypted_message:
        decrypted_message.append(xor(em, key1) ^ xor(em, key2))
    return decrypted_message

if __name__ == '__main__':
    message = [0, 1, 0, 1]
    key1 = 0
    key2 = 1
    encrypted_message = encrypt(message, key1, key2)
    print("Encrypted message:", encrypted_message)
    decrypted_message = decrypt(encrypted_message, key1, key2)
    print("Decrypted message:", decrypted_message)
