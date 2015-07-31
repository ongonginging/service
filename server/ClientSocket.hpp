
#ifndef __CLIENTSOCKET_HPP__
#define __CLIENTSOCKET_HPP__

#include<unistd.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>

class ClientSocket{
    private:
        socklen_t socklen;
        struct sockaddr addr;
        struct sockaddr_in inaddr;
        int  fd;
        int port;
        std::string host;
        bool reopen;
        bool reuse;
        bool nonblocking;
        bool keepAlive;
        int connTimeout;
        int sendTimeout;
        int recvTimeout;
        int sendBuffer;
        int recvBuffer;
        struct linger;
    public:
        ClientSocket(void);
        ClientSocket(bool nonblocking);
        ClientSocket(int fd);
        socklen_t& getSocklen();
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

