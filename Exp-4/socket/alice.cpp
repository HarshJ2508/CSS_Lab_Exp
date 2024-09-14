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
const int ALPHABETS = 26;

string symmetricEncryptCaesarCipher(string plainText, int key) {
    string cipherText = "";
    key = key % ALPHABETS;
    for(auto &p : plainText) {
        const int ALPHABETS = 26;
        cipherText += (char)((p - 'a' + key) % ALPHABETS + 'a');
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

    int q = 353, alpha = 3; // Global Public Elements

    int Xa, Ya = 1; // Xa - private key, Ya - public key
    cout << "Select a private key (Xa)\nNote your private key must be less than " << q << "(q): ";
    cin >> Xa;

    for(int i = 1; i <= Xa; i++) {
        Ya = (alpha * Ya) % q;
    }
    
    cout << "Alice's Public Key: " << Ya << endl;
    cout << "Alice's Private Key: " << Xa << endl;

    // Send Alice's public key
    string public_key = "Alice's Public Key: " + to_string(Ya);
    send(sock, public_key.c_str(), public_key.length(), 0);

    // Receive Bob's public key
    char buffer[1024] = {0};
    recv(sock, buffer, 1024, 0);
    string bob_key(buffer);
    int bob_e, bob_n;
    sscanf(buffer, "Bob's Public Key: %d", &bob_e);
    cout << "Received " << bob_key << endl;

    int Yb = bob_e;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int K = 1; // shared secret key
    for(int i = 1; i <= Xa; i++) {
        K = (K * Yb) % q;
    }

    cout << "The common secret key between you (alice) and bob: " << K << endl;

    // Continuous communication loop
    while (true) {
        // Encrypt and send message
        string plaintext;
        cout << "\n-----------------------------\nEnter plaintext (or 'exit' to quit): ";
        getline(cin, plaintext);

        if (plaintext == "exit") {
            break;
        }

        string ciphertext_str = symmetricEncryptCaesarCipher(plaintext, K);

        ciphertext_str = "Ciphertext: " + ciphertext_str;
        send(sock, ciphertext_str.c_str(), ciphertext_str.length(), 0);

        cout << "Sent: " << ciphertext_str << endl;
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}