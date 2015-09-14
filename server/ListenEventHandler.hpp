
#ifndef __LISTENEVENTHANDLER_HPP__
#define __LISTENEVENTHANDLER_HPP__

#include <event.h>
#include "Listener.hpp"

class Listener;

class ListenEventHandler{
private:
    std::string className = "ListenEventHandler";
    std::weak_ptr<Listener> listener;
    struct event_base* base;
    int listenFd;
    struct event* listenEvent;
    void (* listenCallback)(evutil_socket_t fd, short event, void* arg);

public:
    ListenEventHandler();
    ListenEventHandler(
        const int& listenFd,
        std::shared_ptr<Listener> listener,
        void (* listenCallback)(evutil_socket_t fd, short event, void* arg)
    );
    ~ListenEventHandler();
    void init();
    void serve();
    void shutdown();
};

#endif //__LISTENEVENTHANDLER_HPP__

