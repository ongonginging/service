
#ifndef __LISTENER_HPP__
#define __LISTENER_HPP__

#include<iostream>
#include<event.h>
#include<boost/shared_ptr.hpp>

#include"Configure.hpp"
#include"ServerSocket.hpp"
#include"ListenEventHandler.hpp"

class Listener{
    private:
        std::string className = "Listener";
        boost::shared_ptr<Configure> configure;
        boost::shared_ptr<ServerSocket> serverSocket;
        ListenEventHandler handler;
        friend boost::shared_ptr<ClientSocket> acceptFn(Listener* listener);
    public:
        Listener();
        Listener(const boost::shared_ptr<Configure>& configure);
        ~Listener();
        void init();
        void serve();
        void shutdown();
};

#endif //__LISTENER_HPP__

