
#include "Cycle.hpp"
#include "Configure.hpp"

Cycle::Cycle(){
    this->configure = std::make_shared<Configure>();
}

Cycle::~Cycle(){
}

std::weak_ptr<Configure> Cycle::getConfigure(){
    return std::weak_ptr<Configure>(this->configure);
}

