
#include <iostream>
#include <thread>
#include <memory>

#include "Cycle.hpp"
#include "Configure.hpp"
#include "ServerSocket.hpp"
#include "Listener.hpp"
#include "Dispatcher.hpp"
#include "Log.hpp"

void initConfigure(const std::shared_ptr<Configure>& configure){
    configure->set("port", "9544");
    configure->set("host", "0.0.0.0");
    configure->set("backlog", "1024");
}

void dispatchRunner(const std::weak_ptr<Configure>& configure){
    log("configure.use_count:", configure.use_count());
    Dispatcher disptacher(configure);
    if (!disptacher.init()){
        exit(-1);
    }
    disptacher.serve();
}

void startDispatchMod(const std::weak_ptr<Configure>& configure){
    std::thread dispatchThread(dispatchRunner, configure);
    dispatchThread.join();
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

void ProtoEngineRunner(const std::shared_ptr<Configure>& configure){
}

void startProtoEngineMod(const std::shared_ptr<Configure>& configure){
}

void serviceEngineRunner(const std::shared_ptr<Configure>& configure){
}

void startServiceEngineMod(const std::shared_ptr<Configure>& configure){
}

int main(int argc, char* argv[]){
    log("enter ...");
    int rv = 0;
    std::shared_ptr<Configure> configure(new Configure());
    initConfigure(configure);
    startDispatchMod(configure);
    startProtoEngineMod(configure);
    startServiceEngineMod(configure);
    startListenMod(std::weak_ptr<Configure>(configure));
    log("leave ...");
    return rv;
}

