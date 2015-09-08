
#ifndef __PROTOEVENTHANDLER_HPP__
#define __PROTOEVENTHANDLER_HPP__

#include <event.h>

class ProtoEventHandler{
    private:
        std::string className = "ProtoEventHandler";
        struct event_base* base;
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

