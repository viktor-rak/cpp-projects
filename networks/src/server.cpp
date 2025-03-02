#include <server.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

int Server::startServer() {
    Server::serverSocket = socket(AF_INET, SOCK_STREAM, 0);
}