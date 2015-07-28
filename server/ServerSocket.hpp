
#ifndef __SERVERSOCKET_HPP__
#define __SERVERSOCKET_HPP__

#include<iostream>

class ServerSocket{
    private:
        int fd;
        int backlog;
        int port;
        std::string host;
        bool nonblocking;
        bool reuse;
    public:
        ServerSocket(const int& port, const std::string& host, const int& backlog, const bool& nonblocking);
        ServerSocket(void);
        virtual ~ServerSocket(void);
        virtual int open(void);
        virtual int close(void);
        virtual void serve(void);
};

#endif //__SERVERSOCKET_HPP__
