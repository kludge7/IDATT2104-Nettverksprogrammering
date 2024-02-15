#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <vector>

int calculateResult(int num1, int num2, char operation, int& result) {
    if (operation == '+') {
        result = num1 + num2;
        return 0;
    } else if (operation == '-') {
        result = num1 - num2;
        return 0;
    } else {
        return 1; 
    }
}

void handleClient(int connection) {
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(connection, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';

        int num1, num2, result;
        char operation;
        sscanf(buffer, "%d %c %d", &num1, &operation, &num2);
        std::cout << num1 << operation << num2 << "\n" << std::endl;

        int error = calculateResult(num1, num2, operation, result);

        if(error == 0) {
            write(connection, &result, sizeof(int));
        }
        else {
            const char* errorMessage = "Invalid operation";
            write(connection, errorMessage, strlen(errorMessage) + 1);
        }
    }
    close(connection);
}

int main() {
    const int PORTNR = 1252;

    // Socket for the server
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Server address structure
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET; // Address family (IPv4)
    server_addr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any interface (not necessary since we only use 127.0.0.1)
    server_addr.sin_port = htons(PORTNR); // Port number (Converting to network byte order)

    // Bind the socket to the port and address
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Listen for incoming connections with a waiting list of maximum 3
    listen(server_socket, 3);

    std::cout << "Waiting for connections...\n";

    std::vector<std::thread> threads;

    while (1) {
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);

        // Accept a new client connection
        int connection = accept(server_socket, (struct sockaddr*)&clientAddress, &clientAddressLength);
        std::cout << "Connection with: " << connection << "\n";

        // Create a new thread to handle the new connection
        threads.emplace_back(handleClient, connection);
        threads.back().detach();
    }
    // Not possible to reach here
    close(server_socket);
    return 0;
}