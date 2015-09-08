
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

bool initConfigure(const std::shared_ptr<Cycle>& cycle){
    std::shared_ptr<Configure>& configure = cycle->configure;
    log("0000000000 configure.use_count() = ", configure.use_count());
    configure->set("port", "9544");
    configure->set("host", "0.0.0.0");
    configure->set("backlog", "1024");
    return true;
}

void dispatchRunner(const std::weak_ptr<Cycle>& cycle){
    log("22222222222 cycle.use_count:", cycle.use_count());
    Dispatcher disptacher(cycle);
    if (!disptacher.init()){
        exit(-1);
    }
    disptacher.serve();
}

void listenRunner(const std::weak_ptr<Cycle>& cycle){
    log("22222222222 cycle.use_count:", cycle.use_count());
    Listener listener(cycle);
    if (!listener.init()){
        exit(-1);
    }
    listener.serve();
}

template<typename Fn>
void startModule(Fn fn, const std::weak_ptr<Cycle>& cycle){
    log("11111111111 cycle.use_count:", cycle.use_count());
    try{
        std::thread t(fn, cycle);
        t.detach();
    }catch(const std::exception& e){
        log("exception.what():", e.what());
    }
}

int main(int argc, char* argv[]){
    int rv = 0;
    std::shared_ptr<Cycle> cycle = std::make_shared<Cycle>();
    cycle->configure = std::make_shared<Configure>();
    initConfigure(cycle);
    startModule(dispatchRunner, cycle);
    startModule(listenRunner, cycle);
    cycle->serve();
    return rv;
}

