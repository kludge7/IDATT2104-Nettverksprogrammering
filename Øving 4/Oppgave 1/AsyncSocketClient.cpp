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

    // Create UDP socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);

    // Convert IP address from text to binary form
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    while (true) {
        cout << "Enter a mathematical expression (e.g., 5 + 3): ";
        cin.getline(buffer, MAX_BUFFER_SIZE);

        // Send expression to server
        sendto(clientSocket, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

        // Receive result from server
        recvfrom(clientSocket, result, MAX_BUFFER_SIZE, 0, nullptr, nullptr);

        cout << "Server Response: " << result << endl;
        memset(result, 0, MAX_BUFFER_SIZE);
        memset(buffer, 0, MAX_BUFFER_SIZE);

    }

    // Close the socket
    close(clientSocket);

    return 0;
}
