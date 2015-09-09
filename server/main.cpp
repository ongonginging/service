
#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <functional>

#include "Manager.hpp"
#include "Configure.hpp"
#include "ServerSocket.hpp"
#include "Listener.hpp"
#include "Dispatcher.hpp"
#include "Log.hpp"

bool initConfigure(const std::shared_ptr<Manager>& manager){
    std::shared_ptr<Configure>& configure = manager->configure;
    log("0000000000 configure.use_count() = ", configure.use_count());
    configure->set("port", "9544");
    configure->set("host", "0.0.0.0");
    configure->set("backlog", "1024");
    configure->set("protoThreadNumber", "10");
    configure->set("serviceThreadNumber", "1");
    return true;
}

void dispatchRunner(const std::weak_ptr<Manager>& manager){
    log("22222222222 manager.use_count:", manager.use_count());
    Dispatcher disptacher(manager);
    if (!disptacher.init()){
        exit(-1);
    }
    disptacher.serve();
}

void listenRunner(const std::weak_ptr<Manager>& manager){
    log("22222222222 manager.use_count:", manager.use_count());
    Listener listener(manager);
    if (!listener.init()){
        exit(-1);
    }
    listener.serve();
}

template<typename Fn>
void startModule(Fn fn, const std::weak_ptr<Manager>& manager){
    log("11111111111 manager.use_count:", manager.use_count());
    try{
        std::thread t(fn, manager);
        t.detach();
    }catch(const std::exception& e){
        log("exception.what():", e.what());
    }
}

int main(int argc, char* argv[]){
    int rv = 0;
    std::shared_ptr<Manager> manager = std::make_shared<Manager>();
    manager->configure = std::make_shared<Configure>();
    initConfigure(manager);
    //startModule(dispatchRunner, manager);
    //startModule(listenRunner, manager);
    manager->protoEngine = std::make_shared<ProtoEngine>(manager);
    manager->protoEngine->serve();
    manager->serve();
    return rv;
}

