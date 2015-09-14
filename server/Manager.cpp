
#include <memory>

#include "Manager.hpp"
#include "Configure.hpp"
#include "Listener.hpp"
#include "Dispatcher.hpp"
#include "ProtoEngine.hpp"
#include "ServiceEngine.hpp"
#include "Log.hpp"

Manager::Manager(){
}

Manager::~Manager(){
}

bool Manager::init(){
    bool rv = true;
    this->configure = std::make_shared<Configure>();
    rv = this->configure->parseFromConfigFile();
    if(!rv)return rv;
    this->listener = std::make_shared<Listener>(this->getSharedPtr());
    this->protoEngine = std::make_shared<ProtoEngine>(this->getSharedPtr());
    this->dispatcher = std::make_shared<Dispatcher>(this->getSharedPtr());
    rv = this->listener->init();
    if(!rv)return rv;
    rv = this->protoEngine->init();
    if(!rv)return rv;
    rv = this->dispatcher->init();
    if(!rv)return rv;
    return rv;
}

void Manager::serve(){
    this->protoEngine->serve();
    this->listener->serve();
    this->dispatcher->serve();
}

std::shared_ptr<Manager> Manager::getSharedPtr(){
    return shared_from_this();
}

bool Manager::getConfig(const std::string& key, std::string& value){
    return this->configure->get(key, value);
}

