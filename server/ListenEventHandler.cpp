
#include<iostream>
#include<event.h>
#include"ListenEventHandler.hpp"
#include"Log.hpp"

ListenEventHandler::ListenEventHandler(){
    LOG_ENTER_FUNC("default constructor.");
    LOG_LEAVE_FUNC("default constructor.");
}

ListenEventHandler::~ListenEventHandler(){
    LOG_ENTER_FUNC("default destructor.");
    LOG_LEAVE_FUNC("default destructor.");
}

void ListenEventHandler::init(){
    LOG_ENTER_FUNC("");
    this->base = event_base_new();
    LOG_LEAVE_FUNC("");
}

void ListenEventHandler::setListenCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg){
    this->listenEvent = event_new(this->base, fd, EV_READ|EV_PERSIST, cb, arg);
    event_add(this->listenEvent, NULL);//set event timeout.
}

void ListenEventHandler::serve(){
    LOG_ENTER_FUNC("");
    event_base_dispatch(this->base);
    event_base_free(this->base);
    LOG_LEAVE_FUNC("");
}

void ListenEventHandler::shutdown(){
    LOG_ENTER_FUNC("");
    event_free(this->listenEvent);
    event_base_loopbreak(this->base);
    LOG_LEAVE_FUNC("");
}

