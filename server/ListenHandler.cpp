
#include"ListenHandler.hpp"

ListenHandler::ListenHandler(){
}

ListenHandler::~ListenHandler(){
}

void ListenHandler::init(){
    this->base = event_base_new();
}

void ListenHandler::setCallback(void (* cb)(int fd, short event, void *arg)){
}

void ListenHandler::serve(){
    event_base_dispatch(this->base);
}

void ListenHandler::shutdown(){
}

