#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    const int PORTNR = 1252;
    const char SERVER_IP[] = "127.0.0.1"; 

    // Socket for the client
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Server address structure
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET; // Address family (IPv4)
    server_addr.sin_port = htons(PORTNR); // Port number (Converting to network byte order)

    // Convert server IP address from text to binary form
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // Connect to the server using the created socket and server address
    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    std::cout << "Connected to the server.\n";
    std::cout << "Enter two numbers and an operator (+ or -).\n";
    std::cout << "For example: 1 + 5\n";

    while (1) {
        int num1, num2;
        char operation;
        std::cin >> num1 >> operation >> num2;

        dprintf(client_socket, "%d %c %d", num1, operation, num2);

        int result;
        ssize_t bytesRead = recv(client_socket, &result, sizeof(int), 0);

        if(result == 1635151433) {
            std::cout << "Invalid operation" << std::endl;
            break;
        } else {
            std::cout << "Server response: " << result << std::endl;
        }
    }
    close(client_socket);

    return 0;
}
