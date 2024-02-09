#include <iostream>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024
#define SERVER_PORT 5555

using namespace std;

void performCalculation(char* message, char* result) {
    char operation;
    int num1, num2;

    sscanf(message, "%d %c %d", &num1, &operation, &num2);

    switch (operation) {
        case '+':
            snprintf(result, MAX_BUFFER_SIZE, "%d", num1 + num2);
            break;
        case '-':
            snprintf(result, MAX_BUFFER_SIZE, "%d", num1 - num2);
            break;
        case '*':
            snprintf(result, MAX_BUFFER_SIZE, "%d", num1 * num2);
            break;
        case '/':
            if (num2 != 0) {
                snprintf(result, MAX_BUFFER_SIZE, "%f", static_cast<double>(num1) / num2);
            } else {
                cerr << "Division by zero error" << endl;
                snprintf(result, MAX_BUFFER_SIZE, "Division by zero error");
            }
            break;
        default:
            cerr << "Invalid operation: " << operation << endl;
            snprintf(result, MAX_BUFFER_SIZE, "Invalid operation");
            break;
    }
}

int main() {
    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    socklen_t serverAddressLength = sizeof(serverAddress);
    char buffer[MAX_BUFFER_SIZE];
    char result[MAX_BUFFER_SIZE];

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&serverAddress, 0, serverAddressLength);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(SERVER_PORT);

    ::bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), serverAddressLength);

    cout << "Calculator Server is listening on port " << SERVER_PORT << endl;

    while (1) {
        recvfrom(serverSocket, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr*)&clientAddress, &clientAddressLength);

        performCalculation(buffer, result);
        
        sendto(serverSocket, result, strlen(result), 0, (struct sockaddr*)&clientAddress, clientAddressLength);

    }


    // Close the socket
    close(serverSocket);

    return 0;
}
