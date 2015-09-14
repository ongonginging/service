
#ifndef __SERVICEEVENTHANDLER_HPP__
#define __SERVICEEVENTHANDLER_HPP__

#include <queue>
#include <memory>

#include <event.h>

#include "ServiceEngine.hpp"

class ServiceWorkThread;

class ServiceEventHandler{
    private:
        std::string className = "ServiceEventHandler";
        int taskCtrlChan;
        int threadCtrlChan;
        struct event_base* base;
        struct event* taskCtrlEvent;
        struct event* threadCtrlEvent;
        std::weak_ptr<ServiceWorkThread> workThread;
        void (* taskCtrlCb)(evutil_socket_t fd, short event, void* arg);
        void (* threadCtrlCb)(evutil_socket_t fd, short event, void* arg);
    public:
        ServiceEventHandler();
        ServiceEventHandler(
                int taskCtrlChan,
                int threadCtrlChan,
                std::shared_ptr<ServiceWorkThread> workThread,
                void (* taskCtrlCb)(evutil_socket_t fd, short event, void* arg),
                void (* threadCtrlCb)(evutil_socket_t fd, short event, void* arg)
                );
        ~ServiceEventHandler();
        bool init();
        void serve();
        void shutdown();
};

#endif //__SERVICEEVENTHANDLER_HPP__

