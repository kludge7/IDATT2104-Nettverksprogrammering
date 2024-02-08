#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <vector>

int calculateResult(int num1, int num2, char operation) {
    if (operation == '+') {
        return num1 + num2;
    } else if (operation == '-') {
        return num1 - num2;
    } else {
        return 0; 
    }
}

void handleClient(int connection) {
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = recv(connection, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';

        int num1, num2;
        char operation;
        sscanf(buffer, "%d %d %c", &num1, &num2, &operation);

        int result = calculateResult(num1, num2, operation);

        send(connection, &result, sizeof(int), 0);
    }
    close(connection);
}

int main() {
    const int PORTNR = 1252;

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(PORTNR); 

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    listen(server_socket, 3);

    std::cout << "Server log. Waiting for connections...\n";

    std::vector<std::thread> threads;

    while (true) {
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);

        int connection = accept(server_socket, (struct sockaddr*)&clientAddress, &clientAddressLength);

        threads.emplace_back(handleClient, connection);
        threads.back().detach();
    }
    close(server_socket);
    return 0;
}