
#ifndef __LISTENER_HPP__
#define __LISTENER_HPP__

#include <thread>
#include <memory>
#include <iostream>

#include <event.h>

#include "Event.hpp"
#include "Manager.hpp"
#include "ServerSocket.hpp"
#include "ListenEventHandler.hpp"

struct Manager;
class ListenEventHandler;

class Listener: public std::enable_shared_from_this<Listener>{
    private:
        std::string className = "Listener";
        std::shared_ptr<Manager> manager;
        std::shared_ptr<ServerSocket> serverSocket;
        std::shared_ptr<std::thread> thread;
        std::shared_ptr<ListenEventHandler> eventHandler;
        friend ClientSocket* accept(Listener* listener);
    public:
        Listener();
        Listener(const std::weak_ptr<Manager>& manager);
        ~Listener();
        bool init();
        void serve();
        void shutdown();
        void notifyManager(const EVENT event, const ClientSocket* cs);
        std::shared_ptr<Listener> getSharedPtr();
};

#endif //__LISTENER_HPP__

