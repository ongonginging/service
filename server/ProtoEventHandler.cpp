
#include<iostream>
#include<event.h>
#include"ProtoEventHandler.hpp"
#include"Log.hpp"

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

void ProtoEventHandler::setNotifyCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

void ProtoEventHandler::setParseCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg){
    LOG_ENTER_FUNC("");
    //this->readEvent = event_new(this->base, fd, EV_READ|EV_PERSIST, cb, arg);
    //event_add(this->notifyEvent, NULL);//set event timeout.
    LOG_LEAVE_FUNC("");
}

void ProtoEventHandler::serve(){
    LOG_ENTER_FUNC("");
    event_base_dispatch(this->base);
    event_base_free(this->base);
    LOG_LEAVE_FUNC("");
}

void ProtoEventHandler::shutdown(){
    LOG_ENTER_FUNC("");
    //event_free(this->notifyEvent);
    event_base_loopbreak(this->base);
    LOG_LEAVE_FUNC("");
}

