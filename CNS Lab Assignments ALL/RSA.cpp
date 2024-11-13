#include <iostream>
#include <cmath>

using namespace std;

// Function to calculate GCD of two numbers
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Function to find modular multiplicative inverse
long long modInverse(long long a, long long m) {
    for (long long x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}

// Function for modular exponentiation: (base^exp) % mod
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        // If exp is odd, multiply base with result
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        // exp must be even now
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod; // Square the base
    }
    
    return result;
}

// Function to generate public and private keys
void generateKeys(long long p, long long q, long long& e, long long& d, long long& n) {
    n = p * q; // n is the modulus for public and private keys
    long long phi = (p - 1) * (q - 1); // Euler's totient function

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) {
            break;
        }
        e++;
    }

    // Compute d, the modular multiplicative inverse of e mod phi
    d = modInverse(e, phi);
}

// Function to encrypt plaintext
long long encrypt(long long plaintext, long long e, long long n) {
    return modExp(plaintext, e, n); // Use modular exponentiation
}

// Function to decrypt ciphertext
long long decrypt(long long ciphertext, long long d, long long n) {
    return modExp(ciphertext, d, n); // Use modular exponentiation
}

int main() {
    long long p, q; // Two prime numbers
    cout << "Enter two large prime numbers: ";
    cin >> p >> q;

    long long e, d, n; // Public and private keys
    generateKeys(p, q, e, d, n);

    cout << "Public Key (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private Key (d, n): (" << d << ", " << n << ")" << endl;

    // Example plaintext
    long long plaintext;
    cout << "Enter a plaintext message (integer): ";
    cin >> plaintext;

    // Encryption
    long long ciphertext = encrypt(plaintext, e, n);
    cout << "Encrypted message (ciphertext): " << ciphertext << endl;

    // Decryption
    long long decryptedtext = decrypt(ciphertext, d, n);
    cout << "Decrypted message (plaintext): " << decryptedtext << endl;

    return 0;
}

