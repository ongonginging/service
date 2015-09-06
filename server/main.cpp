
#include <iostream>
#include <thread>
#include <memory>

#include"Configure.hpp"
#include"ServerSocket.hpp"
#include"Listener.hpp"
#include"Log.hpp"

void initConfigure(const std::shared_ptr<Configure>& configure){
    configure->set("port", "9544");
    configure->set("host", "0.0.0.0");
    configure->set("backlog", "1024");
}

void dispatchRunner(const std::shared_ptr<Configure>& configure){
}

void startDispatchMod(const std::shared_ptr<Configure>& configure){
}

void listenRunner(const std::weak_ptr<Configure>& configure){
    log("configure.use_count:", configure.use_count());
    Listener listener(configure);
    if (!listener.init()){
        exit(-1);
    }
    listener.serve();
}

void startListenMod(const std::weak_ptr<Configure>& configure){
    std::thread listenThread(listenRunner, configure);
    listenThread.join();
}

void protocolEngineRunner(const std::shared_ptr<Configure>& configure){
}

void startProtocolEngineMod(const std::shared_ptr<Configure>& configure){
}

void serviceEngineRunner(const std::shared_ptr<Configure>& configure){
}

void startServiceEngineMod(const std::shared_ptr<Configure>& configure){
}

int main(int argc, char* argv[]){
    int rv = 0;
    std::shared_ptr<Configure> configure(new Configure());
    initConfigure(configure);
    startDispatchMod(configure);
    startServiceEngineMod(configure);
    startProtocolEngineMod(configure);
    startListenMod(std::weak_ptr<Configure>(configure));
    return rv;
}

