
#ifndef __CLIENTSOCKET_HPP__
#define __CLIENTSOCKET_HPP__

#include<unistd.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>

class ClientSocket{
    private:
        int  fd;
        struct sockaddr addr;
        struct sockaddr_in inaddr;
        int port;
        std::string host;
        bool reopen;
        bool nonblocking;
    public:
        ClientSocket(void);
        ClientSocket(bool nonblocking);
        ClientSocket(int fd);
        struct sockaddr& getAddr();
        struct sockaddr_in& getInaddr();
        int& getFd();
        int& getPort();
        std::string& getHost();
        virtual ~ClientSocket(void);
        int open(void);
        int close(void);
        int read(const char*& input_buffer);
        int write(const char*& outup_buffer, const int& length);
        std::string toString();
};

#endif //__CLIENTSOCKET_HPP__

