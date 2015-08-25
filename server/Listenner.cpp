
#include<unistd.h>

#include<boost/lexical_cast.hpp>

#include"Listenner.hpp"
#include"ServerSocket.hpp"
#include"ClientSocket.hpp"
#include"Configure.hpp"

static void listenCallback(int fd, short event, void *arg){
    Listener* listener = static_cast<Listener*>(arg);
}

Listener::Listener(){
}

Listener::Listener(const boost::shared_ptr<Configure>& configure){

    int backlog;
    int port;
    std::string host;

    this->configure = configure;

    std::string tmp;
    if(this->configure->get("backlog", tmp)){
        backlog = boost::lexical_cast<int>(tmp);
    }else {
        throw 1;
    }
    if(this->configure->get("port", tmp)){
        port = boost::lexical_cast<int>(tmp);
    }else{
        throw 2;
    }
    if(this->configure->get("host", tmp)){
        host = tmp;
    }else{
        throw 3;
    }

    boost::shared_ptr<ServerSocket> serverSocket(new ServerSocket(port, host, backlog));
    this->serverSocket = serverSocket;
}

Listener::~Listener(){
}

void Listener::init(){
    int rv = this->serverSocket->open();
    this->handler.init();
    this->handler.setListenCallback(listenCallback, this->serverSocket->getFd(), static_cast<void*>(this));
}

void Listener::serve(){
    this->handler.serve();
}

void Listener::shutdown(){
    int rv = this->serverSocket->close();
    this->handler.shutdown();
}

