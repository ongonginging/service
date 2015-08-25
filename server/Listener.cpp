
#include<unistd.h>

#include<boost/lexical_cast.hpp>

#include"Listener.hpp"
#include"ServerSocket.hpp"
#include"ClientSocket.hpp"
#include"Configure.hpp"

static void listenCallback(int fd, short event, void *arg){
}

Listener::Listener(){
}

Listener::Listener(const boost::shared_ptr<Configure>& configure){

    this->configure = configure;

    int backlog;
    int port;
    std::string host;

    std::string tmp;
    bool result = false;
    result = this->configure->get("backlog", tmp);
    if(result){
        backlog = boost::lexical_cast<int>(tmp);
    }
    result = this->configure->get("port", tmp);
    if(result){
        port = boost::lexical_cast<int>(tmp);
    } 
    result = this->configure->get("host", tmp);
    if(result){
        host = tmp;
    } 
    this->serverSocket = ServerSocket(port, host, backlog);
}

Listener::~Listener(){
}

void Listener::init(){
    int rv = this->serverSocket.open();
    this->handler.init();
    this->handler.setCallback(listenCallback, this->serverSocket.getFd(), (void*)this);
}

void Listener::serve(){
    this->handler.serve();
}

void Listener::shutdown(){
    int rv = this->serverSocket.close();
    this->handler.shutdown();
}

