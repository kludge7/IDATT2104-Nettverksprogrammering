#include <iostream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// http://localhost:1337/

// Handle incoming HTTP requests
void handleRequest(int clientSocket) {
    char buffer[4096] = {0};
    std::stringstream header;

    // Receive data from the client into the buffer
    ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));

    std::stringstream clientData(buffer);
    std::string line;

    header << "<UL>";
    // Parse the HTTP request headers line by line
    // The empty line indicates the end of the header
    while (std::getline(clientData, line) && !line.empty()) {
        if (line == "\r") {
            break;
        }
        header << "<LI>" << line << "</LI>";
    }
    header << "</UL>";

    // HTTP response with format specified in task
    std::string httpResponse =
        "HTTP/1.0 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "\r\n"
        "<HTML><BODY>\r\n"
        "<H1>Hilsen. Du har koblet deg opp til min enkle web-tjener </H1>\r\n"
        "<UL>\r\n" +
        header.str() +
        "</UL>\r\n" +
        "</BODY></HTML>";

    // Send the HTTP response to the client
    write(clientSocket, httpResponse.c_str(), httpResponse.size());

    // Close the connection with the client since the client has received the response
    close(clientSocket);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET; // Address family (IPv4)
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any interface
    serverAddr.sin_port = htons(1337); // Port number (Converting to network byte order)

    bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr));

    listen(serverSocket, 1);

    std::cout << "Waiting for connection on port 1337...\n";

    while (1) {
        sockaddr_in clientAddr{};
        socklen_t clientAddrSize = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientAddrSize);

        handleRequest(clientSocket);
    }
    close(serverSocket);
    return 0;
}
