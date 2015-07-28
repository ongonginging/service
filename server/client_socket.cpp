
#include<iostream>
#include<errno.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>

ClientSocket::ClientSocket(void){
    this->reopen = false;
    this->nonblocking = false;
    this->fd = -1;
}

ClientSocket::ClientSocket(bool reopen, bool nonblocking){
    this->reopen = reopen;
    this->nonblocking = nonblocking;
    this->fd = -1;
}

ClientSocket::ClientSocket(int fd){
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
            this->nonblocking = (&O_NONBLOCK)>0?true:false; 
        }
    }else{
        std::cout<<__func__<<" fd(client socket)<0."<<std::endl;
    }
}

ClientSocket::~ClientSocket(void){
    int rv = 0;
    if(this->fd < 0){
        std::cout<<__func__<<"fd(client socket)<0."<<std::endl;
    }
}

int ClientSocket::open(void){
    int rv = 0;
    if(this->fd >= 0){
        std::cout<<__func__<<" fd>0 when openning socket."<<std::endl;
        if (reopen){
            std::cout<<<__func__<<" we intent to close current fd "<<this->fd<<" and create new one."<<std::endl;
            int result = this->close();
            if (result == -1){
                rv = -1;
                return rv;
            } 
        }else{
            std::cout<<<__func__<<" we intent to reuse current fd "<<this->fd<<"."<<std::endl;
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
    int rv = 0;
    int result = -1;
    if(this->fd>=0){
        result = ::close(this->fd);
        if (result == -1){
            std::cout<<__func__<<" there is something wrong when closing socket "<<this->fd<<". errno = "<<result<<std::endl;
            rv = -1;
        }
    }else{
        std::cout<<__func__<<" we would not close client socket. fd<0."<<std::endl;
        return -1;
    }
    return rv;
}

int ClientSocket::read(const char* input_buffer){

}

int ClientSocket::write(const char* outup_buffer){

}
