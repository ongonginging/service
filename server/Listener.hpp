
#ifndef __LISTENER_H__
#define __LISTENER_H__

#include<iostream>

class Listener{
    private:
        bool nonblocking;
        bool reuseAddr;
        int backLog;
        int port;
        std::string host;
    public:
        virtual void serve(void);
};

#endif //__LISTENER_H__
