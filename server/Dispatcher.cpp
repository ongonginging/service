
#include<unistd.h>

#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "Log.hpp"
#include "Manager.hpp"
#include "Event.hpp"
#include "Dispatcher.hpp"
#include "ClientSocket.hpp"

Dispatcher::Dispatcher(const std::weak_ptr<Manager>& manager){
    LOG_ENTER_FUNC("constructor");
    if(manager.expired()){
        exit(1);
    }
    this->manager = manager.lock();
    log("manager.use_count()", this->manager.use_count());
    LOG_LEAVE_FUNC("constructor");
}

Dispatcher::~Dispatcher(){
    LOG_ENTER_FUNC("destructor");
    LOG_LEAVE_FUNC("destructor");
}

void Dispatcher::notifyProtoEngine(const EVENT id, const ClientSocket* cs){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

void Dispatcher::notifyServiceEngine(const EVENT id, const std::string protocol){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

bool Dispatcher::init(){
    bool rv = true;
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
    return rv;
}

void Dispatcher::serve(){
    //LOG_ENTER_FUNC(""); //这里打开会报错, ImportError: No module named 'libstdcxx'''
    while(true){
        sleep(1);
//        log("in loop.");
    }
    LOG_LEAVE_FUNC("");
}

void Dispatcher::shutdown(){
}

