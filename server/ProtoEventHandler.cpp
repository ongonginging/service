
#include <iostream>
#include <memory>
#include <event.h>

#include "Log.hpp"
#include "ProtoEventHandler.hpp"

ProtoEventHandler::ProtoEventHandler(){
    LOG_ENTER_FUNC("default constructor.");
    LOG_LEAVE_FUNC("default constructor.");
}

ProtoEventHandler::ProtoEventHandler(
                int connCtrlChan,
                int threadCtrlChan,
                std::shared_ptr<WorkThread> workThread,
                void (* connReadCb)(evutil_socket_t fd, short event, void* arg),
                void (* connCtrlCb)(evutil_socket_t fd, short event, void* arg),
                void (* threadCtrlCb)(evutil_socket_t fd, short event, void* arg)
                )
{
    LOG_ENTER_FUNC("");
    this->base = event_base_new();
    this->workThread = workThread;
    log("workThred.use_count() = ", workThread.use_count()); 
    log("this->workThred.use_count() = ", this->workThread.use_count()); 

    this->connReadCb = connReadCb;

    this->connCtrlCb = connCtrlCb;
    this->connCtrlEvent = event_new(this->base, this->connCtrlChan, EV_READ|EV_PERSIST, this->connCtrlCb, reinterpret_cast<void*>(workThread.get()));
    event_add(this->connCtrlEvent, NULL);//set event timeout.

    this->threadCtrlCb = threadCtrlCb;
    this->connCtrlEvent = event_new(this->base, this->threadCtrlChan, EV_READ|EV_PERSIST, this->threadCtrlCb, reinterpret_cast<void*>(workThread.get()));
    event_add(this->connCtrlEvent, NULL);//set event timeout.

    LOG_LEAVE_FUNC("");
}

ProtoEventHandler::~ProtoEventHandler(){
    LOG_ENTER_FUNC("default destructor.");
    LOG_LEAVE_FUNC("default destructor.");
}

void ProtoEventHandler::init(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

void ProtoEventHandler::serve(){
    LOG_ENTER_FUNC("");
    event_base_dispatch(this->base);
    event_base_free(this->base);
    LOG_LEAVE_FUNC("");
}

//todo:在ThreadCtrlChanCallback函数里调用这个函数
void ProtoEventHandler::shutdown(){
    LOG_ENTER_FUNC("");
    close(this->connCtrlChan);
    close(this->threadCtrlChan);
    event_free(this->threadCtrlEvent);
    event_free(this->connCtrlEvent);
    //todo: free all connections
    event_base_loopbreak(this->base);
    LOG_LEAVE_FUNC("");
}

bool addConn(int fd, void* arg){
    //struct event* ev = event_new(this->base, fd, EV_READ|EV_PERSIST, cb, arg);
    //event_add(ev, NULL);//set event timeout.
}

bool delConn(){
}

