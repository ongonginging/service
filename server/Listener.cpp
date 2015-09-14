
#include <unistd.h>

#include <map>
#include <thread>
#include <chrono>
#include <atomic>                                                                                                                                                                            
#include <memory>
#include <utility>
#include <iostream>
#include <functional>
#include <unordered_map>

#include <boost/lexical_cast.hpp>

#include "Log.hpp"
#include "Listener.hpp"
#include "ListenEventHandler.hpp"
#include "ServerSocket.hpp"
#include "ClientSocket.hpp"

ClientSocket* accept(Listener* listener){
    GLOBAL_LOG_ENTER_FUNC("");
    return listener->serverSocket->accept();
    GLOBAL_LOG_LEAVE_FUNC("");
}

void listenCallback(evutil_socket_t fd, short event, void *arg){
    GLOBAL_LOG_ENTER_FUNC("");
    Listener* listener = reinterpret_cast<Listener*>(arg);
    while(auto cs = accept(listener)){
        log("accept new client: ", "fd(", cs->getFd(), ")", cs->getHost(),":", cs->getPort());
    }
    GLOBAL_LOG_LEAVE_FUNC("");
}

Listener::Listener(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

Listener::Listener(const std::weak_ptr<Manager>& manager){
    LOG_ENTER_FUNC("");
    int backlog;
    int port;
    std::string host;
    if(manager.expired()){
        //todo: notify main thread to eventHandler error.
        exit(1);
    }
    this->manager = manager.lock();
    log("3333333333333 this->manager.use_count:",this->manager.use_count());
    std::string tmp;
    if(this->manager->getConfig("backlog", tmp)){
        backlog = boost::lexical_cast<int>(tmp);
    }
    if(this->manager->getConfig("port", tmp)){
        port = boost::lexical_cast<int>(tmp);
    }
    if(this->manager->getConfig("host", tmp)){
        host = tmp;
    }
    this->serverSocket = std::make_shared<ServerSocket>(port, host, backlog);
    this->eventHandler = std::make_shared<ListenEventHandler>();
    LOG_LEAVE_FUNC("");
}

Listener::~Listener(){
    LOG_ENTER_FUNC("default destructor");
    LOG_LEAVE_FUNC("default destructor");
}

bool Listener::init(){
    LOG_ENTER_FUNC("");
    bool rv = true;
    int result = this->serverSocket->open();
    log("result =", result);
    if (result<0){
        rv = false;
        return rv;
    }
    this->eventHandler->init();
    this->eventHandler->setListenCallback(listenCallback, this->serverSocket->getFd(), reinterpret_cast<void*>(this));
    LOG_LEAVE_FUNC("");
    return rv;
}

void Listener::serve(){
    LOG_ENTER_FUNC("");
    std::function<void(std::shared_ptr<ListenEventHandler>)> fn = [](std::shared_ptr<ListenEventHandler> sp){return sp->serve();};
    try{
        this->thread = std::make_shared<std::thread>(fn, this->eventHandler);
        this->thread->detach();
        log("start listen thread:", this->thread->get_id());
        log("this->thread.use_count() = ", this->thread.use_count());
    }catch(std::exception& e){
        log("exception info:", e.what());
    }
    LOG_LEAVE_FUNC("");
}

void Listener::shutdown(){
    LOG_ENTER_FUNC("");
    int rv = this->serverSocket->close();
    this->eventHandler->shutdown();
    LOG_LEAVE_FUNC("");
}

