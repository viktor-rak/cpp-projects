#include "../include/client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

Client client;

int Client::conn() {
    struct sockaddr_in servAddr;

}