
#ifndef __LISTENHANDLER_HPP__
#define __LISTENHANDLER_HPP__

#include <event.h>

#include "IEventHandler.hpp"

class ListenHandler: public IEventHandler{
private:
    struct event listenEvent;
public:
    ListenHandler();
    ~ListenHandler();
    void setCallback(void (* cb)(int fd, short event, void *arg));
    void init();
    void serve();
    void shutdown();
};

#endif //__LISTENHANDLER_HPP__

