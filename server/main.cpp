
#include <iostream>
#include <boost/shared_ptr.hpp>

#include"Configure.hpp"
#include"ServerSocket.hpp"
#include"Listener.hpp"

void initConfigure(boost::shared_ptr<Configure>& configure){
    configure->set("port", "9544");
    configure->set("host", "0.0.0.0");
    configure->set("backlog", "1024");
}

void runListener(boost::shared_ptr<Configure>& configure){
    Listener listener = Listener(configure);
    listener.init();
    listener.serve();
    listener.shutdown();
}

int main(int argc, char* argv[]){
    int rv = 0;
    boost::shared_ptr<Configure> configure(new Configure());
    initConfigure(configure);
    runListener(configure);
    return rv;
}

