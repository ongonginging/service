
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
    configure->set("protoThreadNumber", "3");
    configure->set("serviceThreadNumber", "1");
    return true;
}

int main(int argc, char* argv[]){
    int rv = 0;
    std::shared_ptr<Manager> manager = std::make_shared<Manager>();
    manager->configure = std::make_shared<Configure>();
    initConfigure(manager);
    manager->listener = std::make_shared<Listener>(manager);
    manager->listener->init();
    manager->listener->serve();
    manager->protoEngine = std::make_shared<ProtoEngine>(manager);
    manager->protoEngine->init();
    manager->protoEngine->serve();
    manager->dispatcher = std::make_shared<Dispatcher>(manager);
    manager->serve();
    return rv;
}

