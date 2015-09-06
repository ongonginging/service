
#ifndef __LISTENER_HPP__
#define __LISTENER_HPP__

#include <iostream>
#include <memory>

#include <event.h>

#include "Configure.hpp"
#include "ServerSocket.hpp"
#include "ListenEventHandler.hpp"

class Listener{
    private:
        std::string className = "Listener";
        std::shared_ptr<Configure> configure;
        std::shared_ptr<ServerSocket> serverSocket;
        ListenEventHandler handler;
        friend ClientSocket* accept(Listener* listener);
    public:
        Listener();
        Listener(std::weak_ptr<Configure> configure);
        ~Listener();
        bool init();
        void serve();
        void shutdown();
};

#endif //__LISTENER_HPP__

