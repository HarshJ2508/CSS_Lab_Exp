#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <limits>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

const int PORT = 8080;
const int ALPHABETS = 26;

string symmetricDecryptCaesarCipher(string ciphertext_str, int key) {
    string plainText = "";
    key = key % ALPHABETS;
    for(auto &c : ciphertext_str) {
        int decode = c - 'a' - key;
        if(decode < 0) decode = c - 'a' + ALPHABETS - key;
        plainText += (char)(decode + 'a');
    }
    return plainText;
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

    int Xb, Yb = 1; // Xb - private key, Yb - public key
    cout << "Select a private key (Xb)\nNote your private key must be less than " << q << "(q): ";
    cin >> Xb;

    for(int i = 1; i <= Xb; i++) {
        Yb = (alpha * Yb) % q;
    }
    
    cout << "Bob's Public Key: " << Yb << endl;
    cout << "Bob's Private Key: " << Xb << endl;

    // Send Bob's public key
    string public_key = "Bob's Public Key: " + to_string(Yb);
    send(sock, public_key.c_str(), public_key.length(), 0);

    // Receive Alice's public key
    char buffer[1024] = {0};
    recv(sock, buffer, 1024, 0);
    string alice_key(buffer);
    int alice_e;
    sscanf(buffer, "Alice's Public Key: %d", &alice_e);
    cout << "Received " << alice_key << endl;

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int Ya = alice_e;

    int K = 1; // shared secret key
    for(int i = 1; i <= Xb; i++) {
        K = (K * Ya) % q;
    }

    cout << "The common secret key between you (bob) and alice: " << K << endl; 
    
  
    // Continuous communication loop
    while (true) {
        // Receive ciphertext
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(sock, buffer, 1024, 0);
        if (bytes_received <= 0) {
            cout << "Connection closed by Alice." << endl;
            break;
        }
        string ciphertext_str(buffer);
        cout << "Received: " << ciphertext_str << endl;
        string plainText = symmetricDecryptCaesarCipher(ciphertext_str.substr(12), K);
        cout << "Decrypted plaintext: " << plainText << "\n----------------------------\n";
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}