
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
        bool nonblocking;
        bool reuse;
    public:
        ServerSocket(const int& port, const std::string& host, const int& backlog);
        ServerSocket(void);
        ~ServerSocket(void);
        int open(void);
        int close(void);
        ClientSocket accept(void);
};

#endif //__SERVERSOCKET_HPP__
