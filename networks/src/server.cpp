#include <server.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>


class SocketFailureException : public std::runtime_error {
    public: 
        explicit SocketFailureException(const std::string message) : std::runtime_error(message) {}
};

int Server::startServer(bool ipv6 = true) {
    try {
        ipv6 == true ? Server::serverSocket = socket(AF_INET6, SOCK_STREAM, 0)
         : Server::serverSocket = socket(AF_INET6, SOCK_STREAM, 0);  
        if (Server::serverSocket == -1)
            throw new SocketFailureException("Socket creation failed. Error code" + (errno));

        Server::serverAddress.sin_family = ipv6 == true ? AF_INET6 : AF_INET;
        Server::serverAddress.sin_addr.s_addr = INADDR_ANY;
        Server::serverAddress.sin_port = htons(Server::port); // this is a stupid line. ofc it should be the same as the port you gave it
        if (bind(Server::serverSocket, (struct sockaddr*)&Server::serverAddress, sizeof(Server::serverAddress)) < 0) {
            //stupid error in my bind. Type Conversion :)
        
        } 
    } catch (const SocketFailureException e) {
        std::cerr << "Err: " << e.what() << std::endl;
    }


}