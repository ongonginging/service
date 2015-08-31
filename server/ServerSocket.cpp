
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

ServerSocket::ServerSocket(){
    std::cout<<__func__<<std::endl;
    this->fd = -1;
    this->backlog = 1024;
    this->port = 9544;
    this->host = "127.0.0.1";
    this->nonblocking = true;
    this->reuse = true;
}

ServerSocket::ServerSocket(const int& port, const std::string& host, const int& backlog){
    std::cout<<__func__<<" enter"<<std::endl;
    this->fd = -1;
    this->port = port;
    this->host = host;
    this->backlog = backlog;
    this->nonblocking = true;
    this->reuse = true;
    std::cout<<__func__<<" leave"<<std::endl;
}

ServerSocket::~ServerSocket(){
    std::cout<<__func__<<std::endl;
    std::cout<<__func__<<" fd = "<<this->fd<<std::endl;
}

int ServerSocket::getFd(){
    return this->fd;
}

void ServerSocket::setFd(int fd){
    this->fd = fd;
}

int ServerSocket::open(){
    std::cout<<__func__<<" enter"<<std::endl;
    int rv = 0;
    do{
        if(this->fd >= 0){
            std::cout<<__func__<<" fd>0 when openning socket."<<std::endl;
            break;//return rv;
        }
        int fd = -1;
        try{
            fd = ::socket(AF_INET, SOCK_STREAM, 0);
        }catch(std::exception& e){
            std::cout<<__func__<<" exception information: "<<e.what()<<std::endl;
        }
        if(fd == -1){
            std::cout<<__func__<<" created listen socket failed. errno = "<<errno<<std::endl;
            rv = -1;
            break;//return rv;
        }else{
            this->fd = fd; 
            std::cout<<__func__<<" successful created listen socket "<<this->fd<<std::endl;
        }
        if(this->reuse){
            int flag = 1;
            int result = setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
            if (result == -1){
                std::cout<<__func__<<" set reuseaddr to listen socket "<<this->fd<<" failed. errno = "<<errno<<std::endl;
                rv = -1;
                break;//return rv;
            }
        }
        if(this->nonblocking){
            int result = fcntl(this->fd, F_SETFL, O_NONBLOCK|fcntl(this->fd, F_GETFL));
            if (result == -1){
                std::cout<<__func__<<" set nonblocking to listen socket "<<this->fd<<" failed. errno = "<<errno<<std::endl;
                rv = -1;
                break;//return rv;
            }
        }
        this->inaddr.sin_family = AF_INET;         
        this->inaddr.sin_port = htons(this->port);     
        if(this->host.length() != 0){
            this->inaddr.sin_addr.s_addr = inet_addr(this->host.c_str());
        }else{
            this->inaddr.sin_addr.s_addr = INADDR_ANY; 
        }
        bzero(&(this->inaddr.sin_zero),8);

        int result = ::bind(this->fd, (const struct sockaddr*)&this->inaddr, sizeof(this->inaddr));
        if (result == -1){
            std::cout<<__func__<<" bind listen socket "<<this->fd<<" to server address failed. errno = "<<errno<<std::endl;
            rv = -1;
            break;//return rv;
        }
        result = ::listen(this->fd, this->backlog);
         if (result == -1){
            std::cout<<__func__<<" listen on socket "<<this->fd<<" failed. errno = "<<errno<<std::endl;
            rv = -1;
            break;//return rv;
        }
    }while(false);
    std::cout<<__func__<<" leave"<<std::endl;
    return rv;
}

int ServerSocket::close(){
    std::cout<<__func__<<" enter"<<std::endl;
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
    std::cout<<__func__<<" leave"<<std::endl;
    return rv;
}

boost::shared_ptr<ClientSocket> ServerSocket::accept(){
    std::cout<<__func__<<" enter"<<std::endl;
    bool rv = false;
    int fd;
    int port; 
    std::string host;
    struct sockaddr addr;
    struct sockaddr_in inaddr;
    socklen_t socklen = sizeof(addr);
    fd = ::accept(this->fd, &addr, &socklen);
    boost::shared_ptr<ClientSocket> cs(new ClientSocket());
    std::cout<<__func__<<" client socket use count = "<<cs.use_count()<<std::endl;
    if (fd>=0){
        rv = true;
        memcpy(&inaddr, &addr, sizeof(inaddr));
        host = inet_ntoa(inaddr.sin_addr);
        port = inaddr.sin_port;
        cs->setFd(fd);
        cs->setPort(port);
        cs->setHost(host);
        cs->setAddr(addr);
        cs->setInaddr(inaddr);
        if(this->reuse){
            cs->setReuse(true);
        }
        if(this->nodelay){
            cs->setNodelay(true);
        }
        if(this->nonblocking){
            cs->setNonblocking(true);
        }
        if(this->keepalive){
            cs->setKeepalive(true);
        }
    }else{
        std::cout<<__func__<<" leave"<<std::endl;
        return NULL;
    }
    std::cout<<__func__<<" leave"<<std::endl;
    return cs;
}

