#ifndef SERVER
#define SERVER

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

class Server {
    public:
    Server(std::string addr, int port); 
    ~Server();

    Server(const Server&) = delete;  //disable copy constructor and shallow copying 
    Server& operator=(const Server&) = delete;
    
    Server(const Server&) noexcept; //move semantics enabled
    Server& operator=(Server&& other) noexcept;

    int startServer(bool ipv6 = true);
    void closeServer();
    int acceptClient();

    private:
    int serverSocket;
    struct sockaddr_in serverAddress;

    int port;

};

#endif