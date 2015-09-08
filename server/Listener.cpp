
#include<unistd.h>

#include<memory>
#include<boost/lexical_cast.hpp>

#include"Log.hpp"
#include"Listener.hpp"
#include"ServerSocket.hpp"
#include"ClientSocket.hpp"

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

Listener::Listener(const std::weak_ptr<Cycle>& cycle){
    LOG_ENTER_FUNC("");
    int backlog;
    int port;
    std::string host;
    if(cycle.expired()){
        //todo: notify main thread to handler error.
        exit(1);
    }
    this->cycle = cycle.lock();
    log("3333333333333 this->cycle.use_count:",this->cycle.use_count());
    std::string tmp;
    if(this->cycle->getConfig("backlog", tmp)){
        backlog = boost::lexical_cast<int>(tmp);
    }
    if(this->cycle->getConfig("port", tmp)){
        port = boost::lexical_cast<int>(tmp);
    }
    if(this->cycle->getConfig("host", tmp)){
        host = tmp;
    }
    this->serverSocket = std::make_shared<ServerSocket>(port, host, backlog);
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
    this->handler.init();
    this->handler.setListenCallback(listenCallback, this->serverSocket->getFd(), reinterpret_cast<void*>(this));
    LOG_LEAVE_FUNC("")
        return rv;
}

void Listener::serve(){
    LOG_ENTER_FUNC("");
    this->handler.serve();
    LOG_LEAVE_FUNC("")
}

void Listener::shutdown(){
    LOG_ENTER_FUNC("");
    int rv = this->serverSocket->close();
    this->handler.shutdown();
    LOG_LEAVE_FUNC("")
}

