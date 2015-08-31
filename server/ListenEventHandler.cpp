
#include<iostream>
#include<event.h>
#include"ListenEventHandler.hpp"

ListenHandler::ListenHandler(){
    std::cout<<__func__<<" enter default constructor."<<std::endl;
    std::cout<<__func__<<" leave default constructor."<<std::endl;
}

ListenHandler::~ListenHandler(){
    std::cout<<__func__<<" enter default destructor."<<std::endl;
    std::cout<<__func__<<" leave default destructor."<<std::endl;
}

void ListenHandler::init(){
    std::cout<<__func__<<" enter init."<<std::endl;
    this->base = event_base_new();
    std::cout<<__func__<<" leave init."<<std::endl;
}

void ListenHandler::setListenCallback(void (* cb)(evutil_socket_t fd, short event, void* arg), evutil_socket_t fd, void* arg){
    this->listenEvent = event_new(this->base, fd, EV_READ|EV_PERSIST, cb, arg);
    event_add(this->listenEvent, NULL);//set event timeout.
}

void ListenHandler::serve(){
    event_base_dispatch(this->base);
    event_base_free(this->base);
}

void ListenHandler::shutdown(){
    event_free(this->listenEvent);
    event_base_loopbreak(this->base);
}

