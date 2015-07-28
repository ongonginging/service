
#ifndef __LISTENER_H__
#define __LISTENER_H__

#include<iostream>
#include<memory>

#include"ServerSocket.hpp"

using namespace std;

class Listener{
    private:
        ServerSocket* pServerSocket;
    public:
        Listener(void);
        virtual ~Listener(void);
        virtual void serve(void);
};

#endif //__LISTENER_H__
