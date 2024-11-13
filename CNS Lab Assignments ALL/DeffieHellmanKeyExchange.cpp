#include <iostream>
#include <cmath>

using namespace std;

// Function to perform modular exponentiation (a^b % mod)
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {  // If exp is odd, multiply base with result
            result = (result * base) % mod;
        }
        exp = exp >> 1;  // Divide exp by 2
        base = (base * base) % mod;  // Square the base
    }

    return result;
}

int main() {
    // Publicly known values (agreed by both parties)
    long long n, g; // p is a prime number, g is a primitive root modulo p

    cout << "Enter a prime number (n): ";
    cin >> n;
    cout << "Enter a value of (g) prime number: ";
    cin >> g;

    // Private keys (secret values chosen by Alice and Bob)
    long long x, y;
    cout << "Enter Alice's private key: ";
    cin >> x;
    cout << "Enter Bob's private key: ";
    cin >> y;

    // Calculate public keys to be shared
    long long A = modExp(g, x, n); // Alice's public key
    long long B = modExp(g, y, n); // Bob's public key

    cout << "Alice's public key (A): " << A << endl;
    cout << "Bob's public key (B): " << B << endl;

    // Calculate the shared secret key
    long long sharedKeyAlice = modExp(B, x, n); // Shared key as calculated by Alice
    long long sharedKeyBob = modExp(A, y, n);   // Shared key as calculated by Bob

    cout << "Shared secret key calculated by Alice(K1): " << sharedKeyAlice << endl;
    cout << "Shared secret key calculated by Bob(K2): " << sharedKeyBob << endl;

    if (sharedKeyAlice == sharedKeyBob) {
        cout << "The key exchange is successful!" << endl;
    } else {
        cout << "The key exchange failed!" << endl;
    }

    return 0;
}

