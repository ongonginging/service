
#ifndef __SERVERSOCKET_HPP__
#define __SERVERSOCKET_HPP__

#include<iostream>

#include"ClientSocket.hpp"

class ServerSocket{
    private:
        int fd;
        int backlog;
        int port;
        std::string host;
        bool reuse;
        bool keepAlive;
        int connTimeout;
        int sendTimeout;
        int recvTimeout;
        int sendBuffer;
        int recvBuffer;
        struct linger;
    public:
        ServerSocket(const int& port, const std::string& host, const int& backlog);
        ServerSocket(void);
        ~ServerSocket(void);
        int open(void);
        int close(void);
        bool accept(ClientSocket& cs);
};

#endif //__SERVERSOCKET_HPP__
