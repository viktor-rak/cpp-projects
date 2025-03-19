#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>

class Client {
    public: 
    int clientSocketFD;
    int connFD;

    sockaddr_in serverAddr;


    Client() : clientSocketFD(), connFD() {}; 
    ~Client() {
        close(clientSocketFD); 
        //check if this is valid file descriptor
    }

    int conn();
    int sendRequest();
    int receive();
    std::string readFromServer();
};




#endif