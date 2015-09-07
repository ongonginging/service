
#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <functional>

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

void listenRunner(const std::weak_ptr<Configure>& configure){
    log("configure.use_count:", configure.use_count());
    Listener listener(configure);
    if (!listener.init()){
        exit(-1);
    }
    listener.serve();
}

void ProtoEngineRunner(const std::weak_ptr<Configure>& configure){
}

void serviceEngineRunner(const std::weak_ptr<Configure>& configure){
}

template<typename Fn>
void startModule(Fn fn, const std::weak_ptr<Configure>& configure){
    try{
        std::thread t(fn, configure);
        t.detach();
        //t.join(); //exception.what(): Invalid argument
    }catch(const std::exception& e){
        log("exception.what():", e.what());
    }
}

int main(int argc, char* argv[]){
    int rv = 0;
    std::shared_ptr<Configure> configure(new Configure());
    initConfigure(configure);
    startModule(dispatchRunner, configure);
    startModule(listenRunner, configure);
    startModule(ProtoEngineRunner, configure);
    startModule(serviceEngineRunner, configure);
    while(true){
        log("in loop");
        sleep(1);
    }
    return rv;
}

