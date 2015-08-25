
#ifndef __IEVENTHANDLER_HPP__
#define __IEVENTHANDLER_HPP__

#include <event.h>

class IEventHandler{
protected:
    struct event_base* base;
public:
    virtual void setCallback(void (* cb)(int fd, short event, void *arg))=0;
    virtual void init()=0;
    virtual void serve()=0;
    virtual void shutdown()=0;
};

#endif //__IEVENTHANDLER_HPP__

