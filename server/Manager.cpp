
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

void Manager::serve(){
    this->dispatcher->serve();
}

bool Manager::getConfig(const std::string& key, std::string& value){
    return this->configure->get(key, value);
}
