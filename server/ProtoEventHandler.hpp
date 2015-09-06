
#ifndef __PROTOEVENTHANDLER_HPP__
#define __PROTOEVENTHANDLER_HPP__

#include <event.h>
#include "IEventHandler.hpp"

class ProtoEventHandler: public IEventHandler{
    private:
        std::string className = "ProtoEventHandler";
        //struct event* notifyEvent;
    public:
        ProtoEventHandler();
        ~ProtoEventHandler();
        void setNotifyCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg);
        void setParseCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg);
        void init();
        void serve();
        void shutdown();
};

#endif //__PROTOEVENTHANDLER_HPP__

