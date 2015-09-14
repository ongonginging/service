
#include<iostream>
#include<event.h>
#include"ListenEventHandler.hpp"
#include"Log.hpp"

ListenEventHandler::ListenEventHandler(){
    LOG_ENTER_FUNC("default constructor.");
    LOG_LEAVE_FUNC("default constructor.");
}

ListenEventHandler::ListenEventHandler(
    const int& listenFd,
    std::shared_ptr<Listener> listener,
    void (* listenCallback)(evutil_socket_t fd, short event, void* arg)
){
    this->base = event_base_new();
    this->listenFd = listenFd;
    this->listener = listener;
    this->listenCallback = listenCallback;
    this->listenEvent = event_new(this->base, this->listenFd, EV_READ|EV_PERSIST, this->listenCallback,  reinterpret_cast<void*>(listener.get()));
    event_add(this->listenEvent, NULL);//set event timeout.
}

ListenEventHandler::~ListenEventHandler(){
    LOG_ENTER_FUNC("default destructor.");
    LOG_LEAVE_FUNC("default destructor.");
}

void ListenEventHandler::init(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
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

