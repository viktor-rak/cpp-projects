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
    void sendHTTPResp();

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
    std::string statusLine;    
    std::string headers;
    std::string body;

    HTTPResponse() : statusLine("HTTP/1.1 200 OK"), headers(""), body("") {}

    std::string buildResponse(int statusCode, std::string& statusMessage, std::string& contentType, std::string& responseBody) {
        std::string response;
        response = "HTTP/1.1 " + std::to_string(statusCode) + " " + statusMessage  + "\r\n";
        response += "Content-Type: " + contentType + "\r\n";
        response += "Content-Length: " + std::to_string(responseBody.length()) + "\r\n";
        response += "Server: TheServer/1.0\r\n";
        response += "\r\n";
        return response;
    }
    
    std::string toString() {
        return statusLine + "\r\n" + headers + "\r\n" + body;
    }
};

#endif