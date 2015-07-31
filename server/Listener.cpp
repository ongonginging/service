
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

    boost::shared_ptr<ServerSocket>ss(new ServerSocket(port, host, backlog));
    this->spServerSocket = ss;
}

Listener::~Listener(){

}

void Listener::start(){
    this->spServerSocket->open();
}

void Listener::serve(){
    bool result = true;
    while(result){
        ClientSocket cs;
        result = this->spServerSocket->accept(cs);
    }
}

void Listener::stop(){
    ClientSocket cs = this->spServerSocket->close();
}


