#include <iostream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// http://localhost:1337/

void handleRequest(int clientSocket) {
    char buffer[4096] = {0};
    std::stringstream header;

    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    std::stringstream clientData(buffer);
    std::string line;
    header << "<UL>";

    while (std::getline(clientData, line) && !line.empty()) {
        if (line == "\r") {
            break;
        }
        header << "<LI>" << line << "</LI>";
    }

    header << "</UL>";

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

    send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0);

    close(clientSocket);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(1337);  

    bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr));

    listen(serverSocket, 1);

    std::cout << "Webtjeneren venter på tilkobling på port 1337...\n";

    while (true) {
        sockaddr_in clientAddr{};
        socklen_t clientAddrSize = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientAddrSize);

        handleRequest(clientSocket);
    }
    close(serverSocket);
    return 0;
}
