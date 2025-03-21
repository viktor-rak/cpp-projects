#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <sstream>

class Server {
public:
    Server();
    Server(std::string addr, int port);
    ~Server();

    int startServer(bool ipv6);
    int serverListen();
    int acceptClient();
    std::vector<char> receiveData();
    void parseHTTP(std::vector<char> a);
    void sendHTTPResp();
    std::string readHTML(const std::string filename);

private:
    int serverSocket;
    int newSocket;
    struct sockaddr_in serverAddress_v4;
    struct sockaddr_in6 serverAddress_v6;
    std::string addr;
    int port;
};

class HTTPResponse {
    public:
    HTTPResponse();

    std::string buildResponse(int statusCode, std::string statusMessage, std::string contentType, std::string responseBody) {
        std::ostringstream oss;
        oss << "HTTP/1.1 " << statusCode << " " << statusMessage << "\r\n"
            << "Content-Type: " << contentType << "\r\n"
            << "Content-Length: " << responseBody.size() << "\r\n"
            << "Connection: keep-alive\r\n"
            << "\r\n"  
            << responseBody; 
    
        return oss.str();
    }
};

#endif