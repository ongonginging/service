
#include<unistd.h>

#include<boost/lexical_cast.hpp>

#include"Listener.hpp"
#include"ServerSocket.hpp"
#include"ClientSocket.hpp"
#include"Configure.hpp"
#include"Log.hpp"

ClientSocket* accept(Listener* listener){
    GLOBAL_LOG_ENTER_FUNC("");
    return listener->serverSocket->accept();
    GLOBAL_LOG_LEAVE_FUNC("");
}

void listenCallback(evutil_socket_t fd, short event, void *arg){
    GLOBAL_LOG_ENTER_FUNC("");
    Listener* listener = static_cast<Listener*>(arg);
    while(auto cs = accept(listener)){
        log("accept new client: ", "fd(", cs->getFd(), ")", cs->getHost(),":", cs->getPort());
    }
    GLOBAL_LOG_LEAVE_FUNC("");
}

Listener::Listener(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

Listener::Listener(const boost::shared_ptr<Configure>& configure){
    LOG_ENTER_FUNC("");
    int backlog;
    int port;
    std::string host;

    this->configure = configure;

    std::string tmp;
    if(this->configure->get("backlog", tmp)){
        backlog = boost::lexical_cast<int>(tmp);
    }
    if(this->configure->get("port", tmp)){
        port = boost::lexical_cast<int>(tmp);
    }
    if(this->configure->get("host", tmp)){
        host = tmp;
    }
    boost::shared_ptr<ServerSocket> serverSocket(new ServerSocket(port, host, backlog));
    this->serverSocket = serverSocket;
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
    this->handler.setListenCallback(listenCallback, this->serverSocket->getFd(), static_cast<void*>(this));
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

