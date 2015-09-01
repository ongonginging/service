
#include <iostream>
#include <thread>
#include <boost/shared_ptr.hpp>

#include"Configure.hpp"
#include"ServerSocket.hpp"
#include"Listener.hpp"

void initConfigure(boost::shared_ptr<Configure>& configure){
    configure->set("port", "9544");
    configure->set("host", "0.0.0.0");
    configure->set("backlog", "1024");
}

void listenRunner(const boost::shared_ptr<Configure>& configure){
    Listener listener = Listener(configure);
    listener.init();
    listener.serve();
    listener.shutdown();
}

void dispacherRunner(const boost::shared_ptr<Configure>& configure){
}

int main(int argc, char* argv[]){
    int rv = 0;
    boost::shared_ptr<Configure> configure(new Configure());
    initConfigure(configure);
    std::function<void(const boost::shared_ptr<Configure>& configure)> fn;
    std::thread listenThread(listenRunner, configure);
    listenThread.join();
    return rv;
}

