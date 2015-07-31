
#include<iostream>
#include<errno.h>
#include<unistd.h>

#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<arpa/inet.h>

#include"ClientSocket.hpp"

ClientSocket::ClientSocket(void){
    std::cout<<__func__<<" default constructor."<<std::endl;
    this->reopen = false;
    this->nonblocking = false;
    this->fd = -1;
}

ClientSocket::ClientSocket(bool nonblocking){
    std::cout<<__func__<<" customer(bool nonblocking) constructor."<<std::endl;
    this->reopen = false;
    this->nonblocking = nonblocking;
    this->fd = -1;
}

ClientSocket::ClientSocket(int fd){
    std::cout<<__func__<<" customer(int fd) constuctor."<<std::endl;
    this->fd = -1;
    int result = 0;
    if(fd >= 0){
        this->fd = fd;
        this->reopen = false;
        this->nonblocking = false;
        result = fcntl(this->fd, F_GETFL);
        if (result == -1){
            std::cout<<__func__<<" set nonblocking to client socket "<<this->fd<<" failed. errno = "<<errno<<std::endl;
        }else{
            this->nonblocking = (result&O_NONBLOCK)>0?true:false; 
        }
    }else{
        std::cout<<__func__<<" fd(client socket)<0."<<std::endl;
    }
}

ClientSocket::~ClientSocket(void){
    std::cout<<__func__<<" default destructor."<<std::endl;
}

int ClientSocket::open(void){
    std::cout<<__func__<<std::endl;
    int rv = 0;
    if(this->fd >= 0){
        std::cout<<__func__<<" fd>0 when openning socket."<<std::endl;
        if (reopen){
            std::cout<<__func__<<" we intent to close current fd "<<this->fd<<" and create new one."<<std::endl;
            int result = this->close();
            if (result == -1){
                rv = -1;
                return rv;
            } 
        }else{
            std::cout<<__func__<<" we intent to reuse current fd "<<this->fd<<"."<<std::endl;
        }
    }
    int fd = -1;
    fd = ::socket(AF_INET, SOCK_STREAM, 0);
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

int ClientSocket::close(void){
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

int& ClientSocket::getPort(){
    return this->port;
}

std::string& ClientSocket::getHost(){
    return this->host;
}

int& ClientSocket::getFd(){
    return this->fd;
}

struct sockaddr& ClientSocket::getAddr(){
    return this->addr;
}

struct sockaddr_in& ClientSocket::getInaddr(){
    return this->inaddr;
}

int ClientSocket::read(const char*& input_buffer){
    std::cout<<__func__<<std::endl;
}

int ClientSocket::write(const char*& outup_buffer, const int& length){
    std::cout<<__func__<<std::endl;
}

std::string ClientSocket::toString(){
    std::cout<<"{ClientSocket:"<<this<<", fd:"<<this->fd<<", nonblocking:"<<this->nonblocking<<", reopen:"<<this->reopen<<", host:"<<this->host<<", port:"<<this->port<<"}"<<std::endl;
}
