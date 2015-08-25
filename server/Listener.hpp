
#ifndef __LISTENER_HPP__
#define __LISTENER_HPP__

#include<iostream>

#include <boost/shared_ptr.hpp>

#include"Configure.hpp"
#include"ServerSocket.hpp"
#include"ListenHandler.hpp"

class Listener{
    private:
        boost::shared_ptr<Configure> spConfigure;
        ServerSocket serverSocket;
        ListenHandler listenHandler;
    public:
        Listener();
        Listener(const boost::shared_ptr<Configure>& spConfigure);
        ~Listener();
        void start();
        void serve();
        void stop();
};

#endif //__LISTENER_HPP__

