#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <string>
#include <algorithm>

#pragma comment(lib, "Ws2_32.lib")

const int PORT = 8080;
const int MAX_CLIENTS = 2;

std::vector<SOCKET> client_sockets;

DWORD WINAPI handle_client(LPVOID lpParam) {
    SOCKET client_socket = (SOCKET)lpParam;
    char buffer[1024] = {0};
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int valread = recv(client_socket, buffer, 1024, 0);
        if (valread <= 0) {
            std::cout << "Client disconnected" << std::endl;
            break;
        }
        std::cout << "Message received: " << buffer << std::endl;
        
        // Send the message to all other clients
        for (SOCKET sock : client_sockets) {
            if (sock != client_socket) {
                send(sock, buffer, strlen(buffer), 0);
            }
        }
    }
    // Remove the disconnected client from the vector
    client_sockets.erase(std::remove(client_sockets.begin(), client_sockets.end(), client_socket), client_sockets.end());
    closesocket(client_socket);
    return 0;
}

int main() {
    WSADATA wsaData;
    SOCKET server_fd = INVALID_SOCKET;
    struct sockaddr_in address;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup failed" << std::endl;
        return 1;
    }

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cout << "Socket creation error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cout << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        std::cout << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true) {
        SOCKET new_socket;
        int addrlen = sizeof(address);
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
            std::cout << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }
        client_sockets.push_back(new_socket);
        std::cout << "New client connected. Total clients: " << client_sockets.size() << std::endl;

        // Create a new thread for each client
        CreateThread(NULL, 0, handle_client, (LPVOID)new_socket, 0, NULL);
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}