
#include "Listener.hpp"

Listener::Listener(){

}

Listener::Listener(const boost::shared_ptr<Configure>& spConfigure, const boost::shared_ptr<ServerSocket>& spServerSocket){
    this->spConfigure = spConfigure;
    this->spServerSocket = spServerSocket;
}

Listener::~Listener(){

}

void Listener::serve(void){
}


