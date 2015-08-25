
#ifndef __LISTENER_HPP__
#define __LISTENER_HPP__

#include<iostream>
#include <boost/shared_ptr.hpp>

#include"Configure.hpp"
#include"ServerSocket.hpp"
#include"ListenHandler.hpp"

class Listener{
    private:
        boost::shared_ptr<Configure> configure;
        ServerSocket serverSocket;
        ListenHandler handler;
    public:
        Listener();
        Listener(const boost::shared_ptr<Configure>& configure);
        ~Listener();
        void init();
        void serve();
        void shutdown();
};

#endif //__LISTENER_HPP__

