#ifndef SERVER
#define SERVER

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

class Server {
    public:
    Server(std::string addr, int port);
    ~Server();
    int startServer();

    private:
    int serverSocket;
    struct sockaddr_in serverAddress;


};

#endif