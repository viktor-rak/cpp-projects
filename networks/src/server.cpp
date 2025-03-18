#include "../include/server.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>

Server::Server() : addr("127.0.0.1"), port(8080) {} 

Server::Server(std::string addr, int port) 
: addr(addr), port(port) {}   

Server::~Server() {
    close(serverSocket);
}


class SocketFailureException : public std::runtime_error {
    public: 
        explicit SocketFailureException(const std::string message) : std::runtime_error(message) {}
};

int Server::startServer(bool ipv6) {
    try {
        serverSocket = socket(ipv6 ? AF_INET6 : AF_INET, SOCK_STREAM, 0);
        if (Server::serverSocket == -1)
            throw new SocketFailureException("Socket creation failed. Error code" + (errno));

        if (ipv6) {
            Server::serverAddress_v6.sin6_family = AF_INET6;
            Server::serverAddress_v6.sin6_addr = in6addr_any;
            Server::serverAddress_v6.sin6_port = htons(Server::port); // this is a stupid line. ofc it should be the same as the port you gave it
            if (bind(Server::serverSocket, reinterpret_cast<struct sockaddr*>(&this->serverAddress_v6), sizeof(Server::serverAddress_v6)) < 0) {
            }
        } else {
            Server::serverAddress_v4.sin_family = AF_INET;
            Server::serverAddress_v4.sin_addr.s_addr = INADDR_ANY;
            Server::serverAddress_v4.sin_port = htons(Server::port); // this is a stupid line. ofc it should be the same as the port you gave it
            if (bind(Server::serverSocket, reinterpret_cast<struct sockaddr*> (&this->serverAddress_v4), sizeof(Server::serverAddress_v4)) < 0) {               // stupid error in my bind. Type Conversion :)
                throw std::runtime_error("Failed to bind the server: Err: " + std::to_string(errno));
            }
        }
    } catch (const SocketFailureException e) {
        std::cerr << "Err: " << e.what() << std::endl;
    }

    return 0;
}

int Server::serverListen() {
    if (listen(Server::serverSocket, 5) < 0) {
        throw std::runtime_error("Failed to begin listening. Err:" + std::to_string(errno));
    }
    return 0; 
}

int Server::acceptClient() {
    struct sockaddr_in clientAddr;
    socklen_t clientSize = sizeof(clientAddr);
    this->newSocket = accept(Server::serverSocket, (struct sockaddr*)&clientAddr, &clientSize);
    if (Server::newSocket < 0) {
        throw std::runtime_error("Accept error. Err: " + std::to_string(errno));
    }

    return this->newSocket;
}

void Server::sendHTTPResp() {
    HTTPResponse response;
    response.toString();
    send(this->newSocket, response.toString().c_str(), response.toString().size(), 0);
}


int main() {
    try {
        Server server;
        server.startServer(false);
        server.serverListen();
        server.acceptClient();
        server.sendHTTPResp();

    } catch (std::exception e) {
        std::cout << "Oopsie Daisy! HJAHHAHAHAHAHA" << std::endl;
    }
}