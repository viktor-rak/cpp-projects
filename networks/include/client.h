#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

class Client {
    public: 
    int clientSocketFD;
    int connFD;

    Client() : clientSocketFD(socket(AF_INET, SOCK_STREAM, 0)), connFD() {}; 

    int conn();
    std::string readFromServer();
};




#endif