
#ifndef __SERVERSOCKET_HPP__
#define __SERVERSOCKET_HPP__

#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "ClientSocket.hpp"

class ServerSocket{
    private:
        std::string className = "ServerSocket";
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
        int getFd();
        void setFd(int fd);
        ServerSocket(const int& port, const std::string& host, const int& backlog);
        ServerSocket();
        ~ServerSocket();
        int open();
        int close();
        ClientSocket* accept();
};

#endif //__SERVERSOCKET_HPP__

