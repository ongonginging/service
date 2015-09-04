
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
#include"Log.hpp"

ServerSocket::ServerSocket(){
    LOG_ENTER_FUNC(""); 
    this->fd = -1;
    this->backlog = 1024;
    this->port = 9544;
    this->host = "127.0.0.1";
    this->nonblocking = true;
    this->reuse = true;
    LOG_LEAVE_FUNC(""); 
}

ServerSocket::ServerSocket(const int& port, const std::string& host, const int& backlog){
    LOG_ENTER_FUNC(""); 
    this->fd = -1;
    this->port = port;
    this->host = host;
    this->backlog = backlog;
    this->nonblocking = true;
    this->reuse = true;
    LOG_LEAVE_FUNC("");
}

ServerSocket::~ServerSocket(){
    LOG_ENTER_FUNC(""); 
    std::cout<<__func__<<" fd = "<<this->fd<<std::endl;
    LOG_LEAVE_FUNC("");
}

int ServerSocket::getFd(){
    return this->fd;
}

void ServerSocket::setFd(int fd){
    this->fd = fd;
}

int ServerSocket::open(){
    LOG_ENTER_FUNC("");
    int rv = 0;
    do{
        if(this->fd >= 0){
            log("fd>0 when openning socket.");
            break;//return rv;
        }
        int fd = -1;
        try{
            fd = ::socket(AF_INET, SOCK_STREAM, 0);
        }catch(std::exception& e){
            log("exception information:", e.what());
        }
        if(fd == -1){
            log("created listen socket failed. errno =", errno);
            rv = -1;
            break;//return rv;
        }else{
            this->fd = fd; 
            log("successful created listen socket", this->fd);
        }
        if(this->reuse){
            int flag = 1;
            int result = setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
            if (result == -1){
                log("set reuseaddr to listen socket", this->fd, "failed. errno =", errno);
                rv = -1;
                break;//return rv;
            }
        }
        if(this->nonblocking){
            int result = fcntl(this->fd, F_SETFL, O_NONBLOCK|fcntl(this->fd, F_GETFL));
            if (result == -1){
                log("set nonblocking to listen socket", this->fd, "failed. errno =", errno);
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
            log("bind socket", this->fd, "to server address failed. errno =", errno);
            rv = -1;
            break;//return rv;
        }
        result = ::listen(this->fd, this->backlog);
        if (result == -1){
            log("listen socket", this->fd, "failed. errno =", errno);
            rv = -1;
            break;//return rv;
        }
        //std::cout<<"listen on: "<<host<<":"<<port<<std::endl;
        log("listen on", host, ":", port);
    }while(false);
    LOG_LEAVE_FUNC("");
    return rv;
}

int ServerSocket::close(){
    LOG_ENTER_FUNC("");
    int rv = 0;
    int result = -1;
    if(this->fd>=0){
        result = ::close(this->fd);
        if (result == -1){
            log("there is something wrong when closing socket", this->fd, "errno = ", errno);
            rv = -1;
        }else{
            this->fd = -1;
        }
    }else{
        log("we would not close client socket. fd<0.");
        return -1;
    }
    LOG_LEAVE_FUNC("");
    return rv;
}

ClientSocket* ServerSocket::accept(){
    LOG_ENTER_FUNC("");
    struct sockaddr addr;
    struct sockaddr_in inaddr;
    socklen_t socklen = sizeof(addr);
    int fd = ::accept(this->fd, &addr, &socklen);
    ClientSocket* cs = NULL;
    if (fd>=0){
        cs = new ClientSocket();
        memcpy(&inaddr, &addr, sizeof(inaddr));
        cs->setFd(fd);
        cs->setPort(inaddr.sin_port);
        cs->setHost(inet_ntoa(inaddr.sin_addr));
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
    }
    LOG_LEAVE_FUNC("");
    return cs;
}

