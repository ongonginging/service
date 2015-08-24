
#include<unistd.h>

#include<boost/lexical_cast.hpp>

#include"Listener.hpp"
#include"ServerSocket.hpp"
#include"ClientSocket.hpp"
#include"Configure.hpp"

Listener::Listener(){
}

Listener::Listener(const boost::shared_ptr<Configure>& spConfigure){

    this->spConfigure = spConfigure;

    int backlog;
    int port;
    std::string host;

    std::string tmp;
    bool result = false;
    result = this->spConfigure->get("backlog", tmp);
    if(result){
        backlog = boost::lexical_cast<int>(tmp);
    }
    result = this->spConfigure->get("port", tmp);
    if(result){
        port = boost::lexical_cast<int>(tmp);
    } 
    result = this->spConfigure->get("host", tmp);
    if(result){
        host = tmp;
    } 
    this->serverSocket = ServerSocket(port, host, backlog);
}

Listener::~Listener(){
}

void Listener::start(){
    int rv = this->serverSocket.open();
    //todo: add listen fd to event handler.
}

void Listener::serve(){
    //todo: event handler enter loop.
    bool flag = true;
    while(flag){
        boost::shared_ptr<ClientSocket> cs = this->serverSocket.accept();
        if (cs == NULL){
            flag = false;
        }
    }
}

void Listener::stop(){
    //todo: delete listen fd from event handler.
    int rv = this->serverSocket.close();
}


