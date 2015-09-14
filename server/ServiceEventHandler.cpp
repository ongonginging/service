
#include <iostream>
#include <memory>
#include <event.h>

#include "Log.hpp"
#include "ServiceEventHandler.hpp"

ServiceEventHandler::ServiceEventHandler(){
    LOG_ENTER_FUNC("default constructor.");
    LOG_LEAVE_FUNC("default constructor.");
}

ServiceEventHandler::ServiceEventHandler(
                int taskCtrlChan,
                int threadCtrlChan,
                std::shared_ptr<ServiceWorkThread> workThread,
                void (* taskCtrlCb)(evutil_socket_t fd, short event, void* arg),
                void (* threadCtrlCb)(evutil_socket_t fd, short event, void* arg)
                )
{
    LOG_ENTER_FUNC("");

    this->base = event_base_new();
    this->workThread = workThread;
    log("workThread.use_count() = ", workThread.use_count()); 
    log("this->workThread.use_count() = ", this->workThread.use_count()); 

    this->taskCtrlChan = taskCtrlChan;
    this->taskCtrlCb = taskCtrlCb;
    log("this->taskCtrlChan = ", this->taskCtrlChan);
    this->taskCtrlEvent = event_new(this->base, this->taskCtrlChan, EV_READ|EV_PERSIST, this->taskCtrlCb, reinterpret_cast<void*>(workThread.get()));
    event_add(this->taskCtrlEvent, NULL);//set event timeout.

    this->threadCtrlChan = threadCtrlChan;
    this->threadCtrlCb = threadCtrlCb;
    log("this->threadCtrlChan = ", this->threadCtrlChan);
    this->threadCtrlEvent = event_new(this->base, this->threadCtrlChan, EV_READ|EV_PERSIST, this->threadCtrlCb, reinterpret_cast<void*>(workThread.get()));
    event_add(this->taskCtrlEvent, NULL);//set event timeout.

    LOG_LEAVE_FUNC("");
}

ServiceEventHandler::~ServiceEventHandler(){
    LOG_ENTER_FUNC("default destructor.");
    LOG_LEAVE_FUNC("default destructor.");
}

bool ServiceEventHandler::init(){
    bool rv = true;
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
    return rv;
}

void ServiceEventHandler::serve(){
    LOG_ENTER_FUNC("");
    event_base_dispatch(this->base);
    event_base_free(this->base);
    LOG_LEAVE_FUNC("");
}

//todo:在ThreadCtrlChanCallback函数里调用这个函数
void ServiceEventHandler::shutdown(){
    LOG_ENTER_FUNC("");
    close(this->taskCtrlChan);
    close(this->threadCtrlChan);
    event_free(this->threadCtrlEvent);
    event_free(this->taskCtrlEvent);
    //todo: free all connections
    event_base_loopbreak(this->base);
    LOG_LEAVE_FUNC("");
}

