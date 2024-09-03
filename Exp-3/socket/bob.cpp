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

vector<int> decrypt(const vector<int>& ciphertext, int d, int n) {
    vector<int> plaintext;
    for (int c : ciphertext) {
        plaintext.push_back(modPow(c, d, n));
    }
    return plaintext;
}

string symmetricDecryptMonoalphabetic(string ciphertext_str, string decrypted_keyword) {
    string plainText = "";
    for(auto &c : ciphertext_str) {
        for(int i = 0; i < 26; i++) {
            if(decrypted_keyword[i] == c) {
                plainText += (char)(i + 'a');
                break;
            }
        }
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


    int p, q;
    cout << "Enter p: ";
    cin >> p;

    cout << "Enter q: ";
    cin >> q;

    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 7;
    int d = modInverse(e, phi);

    cout << "Bob's Public Key: (e = " << e << ", n = " << n << ")\n";
    cout << "Bob's Private Key: (d = " << d << ", n = " << n << ")\n";

    // Receive Alice's public key
    char buffer[1024] = {0};
    recv(sock, buffer, 1024, 0);
    string alice_key(buffer);
    cout << "Received " << alice_key << endl;

    // Send Bob's public key
    string public_key = "Bob's Public Key: e=" + to_string(e) + " n=" + to_string(n);
    send(sock, public_key.c_str(), public_key.length(), 0);

    char keyWordBuffer[1024] = {0};
    recv(sock, keyWordBuffer, 1024, 0);
    string keyword(keyWordBuffer);
    cout << "Received keyword for symmetric encryption: " << keyword << endl;
    
    // Decrypt the received keyword using Bob's private key
    vector<int> keywordText;
    stringstream ss(keyword);
    int num;
    while (ss >> num) {
        keywordText.push_back(num);
    }
    vector<int> decrypted_keyword_nums = decrypt(keywordText, d, n);
    string decrypted_keyword;
    for (int num : decrypted_keyword_nums) {
        decrypted_keyword += (char)num;  // Convert back from ASCII value
    }
    cout << "Decrypted keyword: " << decrypted_keyword << endl;

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
        string plainText = symmetricDecryptMonoalphabetic(ciphertext_str.substr(12), decrypted_keyword);
        cout << "Decrypted plaintext: " << plainText << "\n----------------------------\n";
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}