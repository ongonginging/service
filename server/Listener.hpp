
#ifndef __LISTENER_HPP__
#define __LISTENER_HPP__

#include <iostream>
#include <memory>

#include <event.h>

#include "Cycle.hpp"
#include "ServerSocket.hpp"
#include "ListenEventHandler.hpp"

struct Cycle;

class Listener{
    private:
        std::string className = "Listener";
        std::shared_ptr<Cycle> cycle;
        std::shared_ptr<ServerSocket> serverSocket;
        ListenEventHandler handler;
        friend ClientSocket* accept(Listener* listener);
    public:
        Listener();
        Listener(const std::shared_ptr<Cycle>& cycle);
        ~Listener();
        bool init();
        void serve();
        void shutdown();
};

#endif //__LISTENER_HPP__

