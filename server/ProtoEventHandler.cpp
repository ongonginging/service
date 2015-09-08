
#include<iostream>
#include<event.h>

#include"Log.hpp"
#include"ProtoEventHandler.hpp"

ProtoEventHandler::ProtoEventHandler(){
    LOG_ENTER_FUNC("default constructor.");
    LOG_LEAVE_FUNC("default constructor.");
}

ProtoEventHandler::~ProtoEventHandler(){
    LOG_ENTER_FUNC("default destructor.");
    LOG_LEAVE_FUNC("default destructor.");
}

void ProtoEventHandler::init(){
    LOG_ENTER_FUNC("");
    this->base = event_base_new();
    LOG_LEAVE_FUNC("");
}

void ProtoEventHandler::setThreadCtrlChanCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg){
    LOG_ENTER_FUNC("");
    this->threadCtrlEvent = event_new(this->base, fd, EV_READ|EV_PERSIST, cb, arg);
    event_add(this->threadCtrlEvent, NULL);//set event timeout.
    LOG_LEAVE_FUNC("");
}

void ProtoEventHandler::setConnCtrlChanCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg){
    LOG_ENTER_FUNC("");
    this->connCtrlEvent = event_new(this->base, fd, EV_READ|EV_PERSIST, cb, arg);
    event_add(this->connCtrlEvent, NULL);//set event timeout.
    LOG_LEAVE_FUNC("");
}

void ProtoEventHandler::setReadConnCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg){
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
    event_free(this->threadCtrlEvent);
    event_free(this->connCtrlEvent);
    //todo: free all connections
    event_base_loopbreak(this->base);
    LOG_LEAVE_FUNC("");
}

