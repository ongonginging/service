
#include<unistd.h>

#include<boost/lexical_cast.hpp>

#include"Listener.hpp"
#include"ServerSocket.hpp"
#include"ClientSocket.hpp"
#include"Configure.hpp"
#include"Log.hpp"

ClientSocket* acceptFn(Listener* listener){
    return listener->serverSocket->accept();
}

void listenCallback(evutil_socket_t fd, short event, void *arg){
    Listener* listener = static_cast<Listener*>(arg);
    while(auto cs = acceptFn(listener)){
        std::cout<<"accept new client: (fd:"<<cs->getFd()<<")"<<cs->getHost()<<":"<<cs->getPort()<<std::endl;
    }
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

void Listener::init(){
    LOG_ENTER_FUNC("");
    int rv = this->serverSocket->open();
    this->handler.init();
    this->handler.setListenCallback(listenCallback, this->serverSocket->getFd(), static_cast<void*>(this));
    LOG_LEAVE_FUNC("")
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

