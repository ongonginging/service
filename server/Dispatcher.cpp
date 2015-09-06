
#include<unistd.h>

#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "Dispatcher.hpp"
#include "Configure.hpp"
#include "ClientSocket.hpp"
#include "Log.hpp"

Dispatcher::Dispatcher(const std::weak_ptr<Configure>& configure){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

Dispatcher::~Dispatcher(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

void Dispatcher::notifyClientSocketEv(const Dispatcher::EVENT& id, const ClientSocket*& cs){
    LOG_ENTER_FUNC("");
    std::unique_lock<std::mutex> lck(this->mtx);
    this->cv.notify_one(); 
    log("notify event");
    this->csEvents.push(std::pair<Dispatcher::EVENT, ClientSocket*>(id, const_cast<ClientSocket*>(cs)));
    LOG_LEAVE_FUNC("");
}

bool Dispatcher::init(){
    bool rv = true;
    return rv;
}

void Dispatcher::serve(){
    LOG_ENTER_FUNC("");
    while(true){
        std::unique_lock<std::mutex> lck(this->mtx);
        while(this->csEvents.size() == 0){
            this->cv.wait(lck);
        }
        while(this->csEvents.size() != 0){
            auto ev = this->csEvents.front();
            this->csEvents.pop();
            //todo: dispatch event to protocol work thread.
            log("process event.");
        }
    }
    LOG_LEAVE_FUNC("");
}

void Dispatcher::shutdown(){
}

