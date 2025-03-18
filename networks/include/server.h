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

    void respond(int statusCode, std::string& statusMessage, std::string& contentType, std::string& responseBody) {
        statusLine = "HTTP/1.1 " + std::to_string(statusCode) + " " + statusMessage;
        headers = "Content-Type: " + contentType + "\r\n";
        headers += "Content-Length: " + std::to_string(responseBody.length()) + "\r\n";
        headers += "Server: TheServer/1.0\r\n";
        body = responseBody;
    }
    
    std::string toString() {
        return statusLine + "\r\n" + headers + "\r\n" + body;
    }
};

#endif