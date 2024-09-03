#include <iostream>
#include <vector>

// Function to compute gcd of a and b
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to compute modular inverse of a under modulo m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // No modular inverse
}

// Function to perform modular exponentiation
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) // If exp is odd, multiply base with result
            result = (result * base) % mod;
        exp = exp >> 1; // exp = exp / 2
        base = (base * base) % mod; // Change base to base^2
    }
    return result;
}

// Function to encrypt a message with given public key (e, n)
std::vector<int> encrypt(const std::vector<int>& plaintext, int e, int n) {
    std::vector<int> ciphertext;
    for (int m : plaintext) {
        ciphertext.push_back(modExp(m, e, n));
    }
    return ciphertext;
}

// Function to decrypt a message with given private key (d, n)
std::vector<int> decrypt(const std::vector<int>& ciphertext, int d, int n) {
    std::vector<int> plaintext;
    for (int c : ciphertext) {
        plaintext.push_back(modExp(c, d, n));
    }
    return plaintext;
}

int main() {
    // Alice's parameters
    int pA = 13, qA = 19;
    int nA = pA * qA; // 247
    int phiA = (pA - 1) * (qA - 1); // 216

    // Choose public exponent e for Alice
    int eA = 5; // Must be coprime with phiA
    int dA = modInverse(eA, phiA); // Compute private exponent d

    std::cout << "Alice's Public Key: (e = " << eA << ", n = " << nA << ")\n";
    std::cout << "Alice's Private Key: (d = " << dA << ", n = " << nA << ")\n";

    // Bob's parameters
    int pB = 17, qB = 23;
    int nB = pB * qB; // 391
    int phiB = (pB - 1) * (qB - 1); // 368

    // Choose public exponent e for Bob
    int eB = 7; // Must be coprime with phiB
    int dB = modInverse(eB, phiB); // Compute private exponent d

    std::cout << "Bob's Public Key: (e = " << eB << ", n = " << nB << ")\n";
    std::cout << "Bob's Private Key: (d = " << dB << ", n = " << nB << ")\n";

    // Encrypt plaintext (using Bob's public key)
    std::string plaintext_str = "harshjain";
    std::vector<int> plaintext;
    for (char c : plaintext_str) {
        plaintext.push_back((int)c - (int)'a'); // Convert char to int (0-25)
    }

    std::vector<int> ciphertext = encrypt(plaintext, eB, nB);

    std::cout << "Ciphertext: ";
    for (int c : ciphertext) {
        std::cout << c << " ";
    }
    std::cout << "\n";

    // Decrypt ciphertext (using Bob's private key)
    std::vector<int> decrypted_plaintext = decrypt(ciphertext, dB, nB);

    std::cout << "Decrypted Plaintext: ";
    for (int m : decrypted_plaintext) {
        if (m >= 0 && m < 26) { // Ensure valid character range
            std::cout << (char)(m + (int)'a'); // Convert int back to char
        } else {
            std::cout << "?"; // Handle out of range values
        }
    }
    std::cout << "\n";

    return 0;
}
