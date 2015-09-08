
#include "Cycle.hpp"
#include "Configure.hpp"
#include "Listener.hpp"
#include "Dispatcher.hpp"
#include "ProtoEngine.hpp"
#include "ServiceEngine.hpp"
#include "Log.hpp"

Cycle::Cycle(){
}

Cycle::~Cycle(){
}

bool Cycle::getConfig(const std::string& key, std::string& value){
    return this->configure->get(key, value);
}
