
#ifndef __LISTENER_HPP__
#define __LISTENER_HPP__

#include <iostream>
#include <memory>

#include <event.h>

#include "Manager.hpp"
#include "ServerSocket.hpp"
#include "ListenEventHandler.hpp"

struct Manager;

class Listener{
    private:
        std::string className = "Listener";
        std::shared_ptr<Manager> manager;
        std::shared_ptr<ServerSocket> serverSocket;
        ListenEventHandler handler;
        friend ClientSocket* accept(Listener* listener);
    public:
        Listener();
        Listener(const std::weak_ptr<Manager>& manager);
        ~Listener();
        bool init();
        void serve();
        void shutdown();
};

#endif //__LISTENER_HPP__

