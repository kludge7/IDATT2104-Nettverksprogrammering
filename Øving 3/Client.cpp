#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    const int PORTNR = 1252;
    const char SERVER_IP[] = "127.0.0.1"; 

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNR);

    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    std::cout << "Connected to the server.";

    while (true) {
        int num1, num2;
        char operation;

        std::cout << "Enter two numbers and an operator (+ or -), separated by spaces: ";
        std::cin >> num1 >> num2 >> operation;

        dprintf(client_socket, "%d %d %c", num1, num2, operation);

        int result;
        ssize_t bytesRead = recv(client_socket, &result, sizeof(int), 0);
    
        std::cout << "Server response: " << result << std::endl;
    }
    close(client_socket);

    return 0;
}
