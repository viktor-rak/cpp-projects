#include "../include/server.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>

Server::Server() : addr("127.0.0.1"), port(8080) {} 

Server::Server(std::string addr, int port) 
: addr(addr), port(port) {}   

Server::~Server() {
    if (serverSocket != -1) {
        close(serverSocket);
    }
}


class SocketFailureException : public std::runtime_error {
    public: 
        explicit SocketFailureException(const std::string message) : std::runtime_error(message) {}
};

int Server::startServer(bool ipv6) {
    try {
        serverSocket = socket(ipv6 ? AF_INET6 : AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1)
            throw SocketFailureException(&"Socket creation failed. Error code" [ (errno)]);

        if (ipv6) {
            serverAddress_v6.sin6_family = AF_INET6;
            serverAddress_v6.sin6_addr = in6addr_any;
            serverAddress_v6.sin6_port = htons(port); // this is a stupid line. ofc it should be the same as the port you gave it
            if (bind(serverSocket, reinterpret_cast<struct sockaddr*>(&this->serverAddress_v6), sizeof(serverAddress_v6)) < 0) {
            }
        } else {
            serverAddress_v4.sin_family = AF_INET;
            serverAddress_v4.sin_addr.s_addr = INADDR_ANY;
            serverAddress_v4.sin_port = htons(port); // this is a stupid line. ofc it should be the same as the port you gave it
            if (bind(serverSocket, reinterpret_cast<struct sockaddr*> (&this->serverAddress_v4), sizeof(serverAddress_v4)) < 0) {               // stupid error in my bind. Type Conversion :)
                throw std::runtime_error("Failed to bind the server: Err: " + std::to_string(errno));
            }
        }
    } catch (const SocketFailureException e) {
        std::cerr << "Err: " << e.what() << std::endl;
    }

    return 0;
}

int Server::serverListen() {
    if (listen(serverSocket, 5) < 0) {
        throw std::runtime_error("Failed to begin listening. Err:" + std::to_string(errno));
    }
    return 0; 
}

int Server::acceptClient() {
    struct sockaddr_in clientAddr;
    socklen_t clientSize = sizeof(clientAddr);
    this->newSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientSize);
    if (newSocket < 0) {
        throw std::runtime_error("Accept error. Err: " + std::to_string(errno));
    }

    return this->newSocket;
}

std::vector<char> Server::receiveData() {
    std::vector<char> buf(1024);
    ssize_t bytes = recv(newSocket, buf.data(), buf.size(), 0); 
    if (bytes < 0) {
        throw std::runtime_error("Failed to receive message. Err: " + std::to_string(errno));
    } 
    if (bytes == 0) {
        throw std::runtime_error("Client closed");
    }
    if (bytes < (ssize_t)buf.size()) {
        buf.resize(bytes);
    }
    return buf;
}

void Server::parseHTTP(std::vector<char> buf) {
    std::string str(buf.begin(), buf.end());
}

void Server::sendHTTPResp() {
    int statusCode = 200;
    std::string statusMessage = "OK";
    std::string contentType = "text/html";
    std::string responseBody;

    try {
        responseBody = readHTML("./index.html");
    } catch (std::runtime_error e) {
        responseBody = "<html><body><h1>500 Internal Server Error</h1></body></html>";
        statusCode = 500;
        statusMessage = "Internal Server Error";
        std::cout << e.what() << std::endl;
    }
    HTTPResponse response;
    std::string a = response.buildResponse(statusCode, statusMessage, contentType, responseBody);
    send(this->newSocket, a.c_str(), a.size(), 0);
}

std::string Server::readHTML(const std::string filename) {
    std::stringstream buf;
    std::string str;
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to find HTML file. Err: " + std::to_string(errno));
    }
    buf << file.rdbuf();
    str = buf.str();
    file.close();
    return str;
}

int main() {
    try {
        Server server;
        int ss = server.startServer(false);
        server.serverListen();
        while (true) { //print debugging
            std::cout << "Waiting for client..." << std::endl;
            server.acceptClient();
            std::cout << "Client connected." << std::endl;
            server.sendHTTPResp();
            std::cout << "Response sent to client." << std::endl;
        }
    } catch (std::exception e) {
        std::cout << "you just hit my bad error handling" << e.what() << std::endl;
    }
}
