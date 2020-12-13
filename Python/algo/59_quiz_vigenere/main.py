from vigenere import generate_key
from vigenere import encrypt
from vigenere import decrypt


if __name__ == '__main__':
    t = 'ATTACK SILICON VALLEY'
    k = generate_key(t, 'HELLO')
    e = encrypt(t, k)
    print(e)
    d = decrypt(e, k)
    print(d)

