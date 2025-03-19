#include "../include/client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>

Client client;

int Client::conn() {
    clientSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    //temp stuff to get basic functionality
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (connect(clientSocketFD, (struct sockaddr*)&this->serverAddr, sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Failed to connect. Err: " + std::to_string(errno));
    }
    return 0;
}

int Client::sendRequest() {
    std::vector<char> request{'h', 'e', 'y'};
    send(clientSocketFD, request.data(), request.size(), 0);
    return 0;
}

int Client::receive() {
    std::vector<char> buffer(1024);
    std::string output;
    int msg = recv(clientSocketFD, buffer.data(), sizeof(buffer), 0);
    if (msg < 0) {
        throw std::runtime_error("Failed to receive: " + std::to_string(errno));
    }
    while (msg > 0) {
        output.append(buffer.data(), msg);
        msg = recv(clientSocketFD, buffer.data(), sizeof(buffer), 0);
    }
    std::cout << output << std::endl;
    return 0;
}

int main() {
    Client client;
    client.conn();
    client.sendRequest();
    client.receive();
    return 0;
}