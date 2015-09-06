
#include "Cycle.hpp"
#include "Configure.hpp"
#include "Log.hpp"

Cycle::Cycle(){
    this->configure = std::make_shared<Configure>();
    log("use_count: ", this->configure.use_count());
}

Cycle::~Cycle(){
}

std::weak_ptr<Configure> Cycle::getConfigure(){
    return std::weak_ptr<Configure>(this->configure);
}

