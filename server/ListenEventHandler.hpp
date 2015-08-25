
#ifndef __LISTENEVENTHANDLER_HPP__
#define __LISTENEVENTHANDLER_HPP__

#include <event.h>
#include "IEventHandler.hpp"

class ListenHandler: public IEventHandler{
private:
    struct event* listenEvent;
public:
    ListenHandler();
    ~ListenHandler();
    void setListenCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg);
    void init();
    void serve();
    void shutdown();
};

#endif //__LISTENEVENTHANDLER_HPP__

