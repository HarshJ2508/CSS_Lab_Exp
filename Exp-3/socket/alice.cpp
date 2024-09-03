#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <limits>
#include <vector>
#include <cmath>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

const int PORT = 8080;

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

int modPow(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

vector<int> encrypt(const vector<int>& plaintext, int e, int n) {
    vector<int> ciphertext;
    for (int m : plaintext) {
        ciphertext.push_back(modPow(m, e, n));
    }
    return ciphertext;
}


string symmetricEncryptMonoalphabetic(string plainText, string key) {
    string cipherText = "";
    for(auto &p : plainText) {
        cipherText += key[p - 'a'];
    }
    return cipherText;
}

int main() {
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in serv_addr;
    
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup failed" << std::endl;
        return 1;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cout << "Socket creation error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cout << "Connection Failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server" << std::endl;

    int p, q;
    cout << "Enter p: ";
    cin >> p;

    cout << "Enter q: ";
    cin >> q;

    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 5;
    int d = modInverse(e, phi);

    cout << "Alice's Public Key: (e = " << e << ", n = " << n << ")\n";
    cout << "Alice's Private Key: (d = " << d << ", n = " << n << ")\n";

    // Send Alice's public key
    string public_key = "Alice's Public Key: e=" + to_string(e) + " n=" + to_string(n);
    send(sock, public_key.c_str(), public_key.length(), 0);

    // Receive Bob's public key
    char buffer[1024] = {0};
    recv(sock, buffer, 1024, 0);
    string bob_key(buffer);
    int bob_e, bob_n;
    sscanf(buffer, "Bob's Public Key: e=%d n=%d", &bob_e, &bob_n);
    cout << "Received " << bob_key << endl;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Keyword for symmetric encryption
    string keyword;
    cout << "\n____________________________\nUsing Monoalphabetic Cipher as symmetric encryption\n____________________________\n";
    for(int i = 0; i < 26; i++) {
        char ch;
        cout << "Map " << (char)(i + 'a') << " with ";
        cin >> ch;
        keyword += ch;
        cout << endl;
    }

    // Encrypt the keyword using Bob's public key
    vector<int> keyword_nums;
    for (char c : keyword) {
        keyword_nums.push_back((int)c);  
    }
    vector<int> keyword_cipher = encrypt(keyword_nums, bob_e, bob_n);
    string encrypted_keyword;
    for (int num : keyword_cipher) {
        encrypted_keyword += to_string(num) + " ";
    }
    send(sock, encrypted_keyword.c_str(), encrypted_keyword.length(), 0);

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Continuous communication loop
    while (true) {
        // Encrypt and send message
        string plaintext;
        cout << "\n-----------------------------\nEnter plaintext (or 'exit' to quit): ";
        getline(cin, plaintext);

        if (plaintext == "exit") {
            break;
        }

        string ciphertext_str = symmetricEncryptMonoalphabetic(plaintext, keyword);

        ciphertext_str = "Ciphertext: " + ciphertext_str;
        send(sock, ciphertext_str.c_str(), ciphertext_str.length(), 0);

        cout << "Sent: " << ciphertext_str << endl;
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}