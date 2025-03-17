#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

class Server {
    public:
    Server();
    Server(std::string addr, int port);
    ~Server();

    int startServer(bool ipv6);
    int serverListen();
    int acceptClient();
    int sendHello();

    private:
    int serverSocket;
    int newSocket;
    struct sockaddr_in serverAddress_v4;
    struct sockaddr_in6 serverAddress_v6;
    std::string addr;
    int port;

};

#endif