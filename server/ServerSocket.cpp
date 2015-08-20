
#include<iostream>
#include<errno.h>
#include<unistd.h>
#include<string.h>

#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include"ServerSocket.hpp"
#include"ClientSocket.hpp"

ServerSocket::ServerSocket(void){
    std::cout<<__func__<<std::endl;
    this->fd = -1;
    this->backlog = 1024;
    this->port = 9544;
    this->host = "127.0.0.1";
    this->nonblocking = true;
    this->reuse = true;
}

ServerSocket::ServerSocket(const int& port, const std::string& host, const int& backlog){
    std::cout<<__func__<<std::endl;
    this->fd = -1;
    this->port = port;
    this->host = host;
    this->backlog = backlog;
    this->nonblocking = true;
    this->reuse = true;
}

ServerSocket::~ServerSocket(void){
    std::cout<<__func__<<std::endl;
    std::cout<<__func__<<" fd = "<<this->fd<<std::endl;
}

int ServerSocket::open(void){
    std::cout<<__func__<<std::endl;
    int rv = 0;
    if(this->fd >= 0){
        std::cout<<__func__<<" fd>0 when openning socket."<<std::endl;
        return rv;
    }
    int fd = -1;
    try{
        fd = ::socket(AF_INET, SOCK_STREAM, 0);
    }catch(std::exception& e){
        std::cout<<__func__<<" exception information: "<<e.what()<<std::endl;
    }
    if(fd == -1){
        std::cout<<__func__<<" created client socket failed. errno = "<<errno<<std::endl;
        return -1;
    }else{
        this->fd = fd; 
        std::cout<<__func__<<" successful created client socket "<<this->fd;
    }
    if(this->nonblocking){
        int result = fcntl(this->fd, F_SETFL, O_NONBLOCK|fcntl(this->fd, F_GETFL));
        if (result == -1){
            std::cout<<__func__<<" set nonblocking to client socket "<<this->fd<<" failed. errno = "<<result<<std::endl;
            rv = -1;
        }
    }
    return rv;
}

int ServerSocket::close(void){
    std::cout<<__func__<<std::endl;
    int rv = 0;
    int result = -1;
    if(this->fd>=0){
        result = ::close(this->fd);
        if (result == -1){
            std::cout<<__func__<<" there is something wrong when closing socket "<<this->fd<<". errno = "<<result<<std::endl;
            rv = -1;
        }else{
            this->fd = -1;
        }
    }else{
        std::cout<<__func__<<" we would not close client socket. fd<0."<<std::endl;
        return -1;
    }
    return rv;
}

bool ServerSocket::accept(ClientSocket& cs){
    std::cout<<__func__<<std::endl;
    bool rv = false;
    int fd;
    int port; 
    std::string host;
    struct sockaddr addr;
    struct sockaddr_in inaddr;
    socklen_t socklen = sizeof(addr);
    fd = ::accept(this->fd, &addr, &socklen);
    if (fd>0){
        rv = true;
        memcpy(&inaddr, &addr, sizeof(inaddr));
        host = inet_ntoa(inaddr.sin_addr);
        port = inaddr.sin_port;
        cs.setFd(fd);
        cs.setPort(port);
        cs.setHost(host);
        cs.setAddr(addr);
        cs.setInaddr(inaddr);
        if(this->reuse){
            cs.setReuse(true);
        }
        if(this->nodelay){
            cs.setNodelay(true);
        }
        if(this->nonblocking){
            cs.setNonblocking(true);
        }
        if(this->keepalive){
            cs.setKeepalive(true);
        }
    }
    return rv;
}

