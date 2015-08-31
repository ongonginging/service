
#ifndef __LISTENEVENTHANDLER_HPP__
#define __LISTENEVENTHANDLER_HPP__

#include <event.h>
#include "IEventHandler.hpp"

class ListenEventHandler: public IEventHandler{
private:
    std::string className = "ListenEventHandler";
    struct event* listenEvent;
public:
    ListenEventHandler();
    ~ListenEventHandler();
    void setListenCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg);
    void init();
    void serve();
    void shutdown();
};

#endif //__LISTENEVENTHANDLER_HPP__

