
#ifndef __SERVERSOCKET_HPP__
#define __SERVERSOCKET_HPP__

#include<iostream>

#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include"ClientSocket.hpp"

class ServerSocket{
    private:
        int fd;
        int backlog;
        int port;
        std::string host;
        struct sockaddr_in inaddr;
        bool reuse;
        bool keepalive;
        bool nonblocking;
        bool nodelay;
        int connTimeout;
        int sendTimeout;
        int recvTimeout;
        int sendBuffer;
        int recvBuffer;
        struct linger soLinger;
    public:
        ServerSocket(const int& port, const std::string& host, const int& backlog);
        ServerSocket(void);
        ~ServerSocket(void);
        int open(void);
        int close(void);
        bool accept(ClientSocket& cs);
};

#endif //__SERVERSOCKET_HPP__

