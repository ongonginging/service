
#include "Cycle.hpp"
#include "Configure.hpp"
#include "Listener.hpp"
#include "Dispatcher.hpp"
#include "ProtoEngine.hpp"
#include "ServiceEngine.hpp"
#include "Log.hpp"

Cycle::Cycle(){
    this->configure = std::make_shared<Configure>();
    log("use_count: ", this->configure.use_count());
    this->listener = std::make_shared<Listener>(this->configure);
}

Cycle::~Cycle(){
}

std::weak_ptr<Configure> Cycle::getConfigure(){
    return std::weak_ptr<Configure>(this->configure);
}

