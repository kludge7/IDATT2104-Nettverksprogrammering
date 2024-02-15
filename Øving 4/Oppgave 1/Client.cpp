#include <iostream>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5555

using namespace std;

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[MAX_BUFFER_SIZE];
    char result[MAX_BUFFER_SIZE];
    memset(result, 0, MAX_BUFFER_SIZE);

    // Create a UDP socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Initialize and configure the server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);
    
    std::cout << "Enter two numbers and an operator (+, -, / or *).\n";
    std::cout << "For example: 1*5\n";
    while (true) {
        // Get line from terminal and enter it into buffer
        cin.getline(buffer, MAX_BUFFER_SIZE);

        // Send buffer to server
        sendto(clientSocket, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

        // Get result from server
        recvfrom(clientSocket, result, MAX_BUFFER_SIZE, 0, nullptr, nullptr);
        cout << "Server Response: " << result << endl;

        // Reset buffer and result
        memset(result, 0, MAX_BUFFER_SIZE);
        memset(buffer, 0, MAX_BUFFER_SIZE);
    }
    close(clientSocket);

    return 0;
}
