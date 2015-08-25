
#ifndef __LISTENNER_HPP__
#define __LISTENNER_HPP__

#include<iostream>
#include <boost/shared_ptr.hpp>

#include"Configure.hpp"
#include"ServerSocket.hpp"
#include"ListenEventHandler.hpp"

class Listener{
    private:
        boost::shared_ptr<Configure> configure;
        boost::shared_ptr<ServerSocket> serverSocket;
        ListenHandler handler;
    public:
        Listener();
        Listener(const boost::shared_ptr<Configure>& configure);
        ~Listener();
        void init();
        void serve();
        void shutdown();
};

#endif //__LISTENNER_HPP__

