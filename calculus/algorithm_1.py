import random

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def find_inverse(a, m):
    m0 = m
    y = 0
    x = 1

    if m == 1:
        return 0

    while a > 1:
        q = a // m
        t = m
        m = a % m
        a = t
        t = y
        y = x - q * y
        x = t

    if x < 0:
        x = x + m0

    return x

def f(x, a, b, n):
    return (a * x + b) % n

def encrypt(m, a, b, n):
    return f(m, a, b, n)

def decrypt(c, a_inv, b, n):
    return f(c, a_inv, -b, n)

def generate_key(n):
    while True:
        a = random.randint(2, n - 1)
        if gcd(a, n) == 1:
            break

    b = random.randint(2, n - 1)

    a_inv = find_inverse(a, n)

    return a, b, a_inv

if __name__ == '__main__':
    p = 61
    q = 53
    n = p * q

    m = 12345
    print("Original Message:", m)

    a, b, a_inv = generate_key(n)
    c = encrypt(m, a, b, n)
    print("Encrypted Message:", c)

    m_decrypted = decrypt(c, a_inv, b, n)
    print("Decrypted Message:", m_decrypted)
