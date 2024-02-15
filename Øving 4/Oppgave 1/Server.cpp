#include <iostream>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024
#define SERVER_PORT 5555

using namespace std;

void performCalculation(int num1, int num2, char operation, char* result) {
    switch (operation) {
        case '+':
            // Write the result to 'result'
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
                // Cast the result to double and write it to 'result'
                snprintf(result, MAX_BUFFER_SIZE, "%f", static_cast<double>(num1) / num2);
            } else {
                snprintf(result, MAX_BUFFER_SIZE, "Division by zero error");
            }
            break;
        default:
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

    // Create a UDP socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    // Initialize and configure the server address structure
    memset(&serverAddress, 0, serverAddressLength);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(SERVER_PORT);

    // Bind the socket and specified address and port
    ::bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), serverAddressLength);

    cout << "Waiting for connections on port " << SERVER_PORT << endl;

    while (1) {
        // Recieve data from client and store it in buffer
        recvfrom(serverSocket, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr*)&clientAddress, &clientAddressLength);
        
        char operation;
        int num1, num2;
        // Get information from buffer and store it in local variables
        sscanf(buffer, "%d %c %d", &num1, &operation, &num2);
        std::cout << num1 << operation << num2 << std::endl;
        performCalculation(num1, num2, operation, result);
        
        // Send the result back (char)
        sendto(serverSocket, result, strlen(result), 0, (struct sockaddr*)&clientAddress, clientAddressLength);

    }
    // Close the socket
    close(serverSocket);

    return 0;
}
