
#ifndef __PROTOEVENTHANDLER_HPP__
#define __PROTOEVENTHANDLER_HPP__

#include <queue>
#include <memory>

#include <event.h>

#include "ProtoEngine.hpp"

class WorkThread;

class ProtoEventHandler{
    private:
        std::string className = "ProtoEventHandler";
        int connCtrlChan;
        int threadCtrlChan;
        struct event_base* base;
        struct event* connCtrlEvent;
        struct event* threadCtrlEvent;
        std::queue<struct event*> connEvent;
        std::weak_ptr<WorkThread> workThread;
        void (* connReadCb)(evutil_socket_t fd, short event, void* arg);
        void (* connCtrlCb)(evutil_socket_t fd, short event, void* arg);
        void (* threadCtrlCb)(evutil_socket_t fd, short event, void* arg);
    public:
        ProtoEventHandler();
        ProtoEventHandler(
                int connCtrlChan,
                int threadCtrlChan,
                std::shared_ptr<WorkThread> workThread,
                void (* connReadCb)(evutil_socket_t fd, short event, void* arg),
                void (* connCtrlCb)(evutil_socket_t fd, short event, void* arg),
                void (* threadCtrlCb)(evutil_socket_t fd, short event, void* arg)
                );
        ~ProtoEventHandler();
        void init();
        void serve();
        void shutdown();
        bool addConn(int fd, void* arg);
        bool delConn(int fd);
};

#endif //__PROTOEVENTHANDLER_HPP__

