
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

void dispatchRunner(const boost::shared_ptr<Configure>& configure){
}

void startDispatchMod(const boost::shared_ptr<Configure>& configure){
}

void listenRunner(const boost::shared_ptr<Configure>& configure){
    Listener listener = Listener(configure);
    listener.init();
    listener.serve();
    listener.shutdown();
}

void startListenMod(const boost::shared_ptr<Configure>& configure){
    std::thread listenThread(listenRunner, configure);
    listenThread.join();
}

void protocolEngineRunner(const boost::shared_ptr<Configure>& configure){
}

void startProtocolEngineMod(const boost::shared_ptr<Configure>& configure){
}

void serviceEngineRunner(const boost::shared_ptr<Configure>& configure){
}

void startServiceEngineMod(const boost::shared_ptr<Configure>& configure){
}

int main(int argc, char* argv[]){
    int rv = 0;
    boost::shared_ptr<Configure> configure(new Configure());
    initConfigure(configure);
    startDispatchMod(configure);
    startServiceEngineMod(configure);
    startProtocolEngineMod(configure);
    startListenMod(configure);
    return rv;
}

