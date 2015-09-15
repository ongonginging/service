
#ifndef __CLIENTSOCKET_HPP__
#define __CLIENTSOCKET_HPP__

#include<unistd.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>

class ClientSocket{
    private:
        std::string className = "ClientSocket";
        bool reopen;
        bool closed;

        socklen_t socklen;
        struct sockaddr addr;
        struct sockaddr_in inaddr;
        int fd;
        int port;
        std::string host;

        bool reuse;
        bool nonblocking;
        bool keepalive;
        bool nodelay;
        int connTimeout;
        int sendTimeout;
        int recvTimeout;
        int sendBufferSize;
        int recvBufferSize;
        struct linger soLinger;

    public:
        ClientSocket(void);
        ClientSocket(int fd);
        virtual ~ClientSocket(void);

        socklen_t getSocklen();
        void setSocklen(const socklen_t& socklen);

        struct sockaddr getAddr();
        void setAddr(const struct sockaddr& addr);

        struct sockaddr_in getInaddr();
        void setInaddr(const struct sockaddr_in& inaddr);

        int getFd();
        void setFd(const int& fd);

        int getPort();
        void setPort(const int& port);

        std::string getHost();
        void setHost(const std::string& host);

        bool getReuse();
        void setReuse(const bool& reuse);

        bool getNonblocking();
        void setNonblocking(const bool& nonblocking);

        bool getNodelay();
        void setNodelay(const bool& nodelay);

        bool getKeepalive();
        void setKeepalive(const bool& keepalive);

        int getSendBufferSize();
        void setSendBufferSize(const int& sendBufferSize);

        int getRecvBufferSize();
        void setRecvBufferSize(const int& recvBufferSize);

        int getSendTimeout();
        void setSendTimeout(const int& sendTimeout);

        int getRecvTimeout();
        void setRecvTimeout(const int& recvTimeout);

        int getConnTimeout();
        void setConnTimeout(const int& connTimeout);

        struct linger getLinger();
        void setLinger(const struct linger& soLinger);

        int open(void);
        int close(void);
        int read(const char*& input_buffer);
        int write(const char*& outup_buffer, const int& length);
        std::string toString();
};

#endif //__CLIENTSOCKET_HPP__

