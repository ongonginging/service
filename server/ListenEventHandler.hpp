
#ifndef __LISTENEVENTHANDLER_HPP__
#define __LISTENEVENTHANDLER_HPP__

#include <event.h>

class ListenEventHandler{
private:
    std::string className = "ListenEventHandler";
    struct event_base* base;
    struct event* listenEvent;
    void (* listenCallback)(evutil_socket_t fd, short event, void* arg);
public:
    ListenEventHandler();
    ~ListenEventHandler();
    void setListenCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg);
    void init();
    void serve();
    void shutdown();
};

#endif //__LISTENEVENTHANDLER_HPP__

