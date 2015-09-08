
#ifndef __PROTOEVENTHANDLER_HPP__
#define __PROTOEVENTHANDLER_HPP__

#include <queue>
#include <event.h>

class ProtoEventHandler{
    private:
        std::string className = "ProtoEventHandler";
        struct event_base* base;
        struct event* connCtrlEvent;
        struct event* threadCtrlEvent;
        std::queue<struct event*> connEvent;
    public:
        ProtoEventHandler();
        ~ProtoEventHandler();
        void setThreadCtrlChanCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* ar);
        void setConnCtrlChanCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg);
        void setReadConnCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg);
        void init();
        void serve();
        void shutdown();
};

#endif //__PROTOEVENTHANDLER_HPP__

