
#ifndef __CYCLE_HPP__
#define __CYCLE_HPP__

#include<memory>

#include "Configure.hpp"
#include "Listener.hpp"
#include "Dispatcher.hpp"
#include "ProtoEngine.hpp"
#include "ServiceEngine.hpp"

class Cycle{
    private:
        std::shared_ptr<Configure> configure;
        std::shared_ptr<Dispatcher> dispatcher;
        std::shared_ptr<Listener> listener;
        std::shared_ptr<ProtoEngine> protoEngine;
        std::shared_ptr<ServiceEngine> serviceEngine;
    public:
        Cycle();
        ~Cycle();
        std::weak_ptr<Configure> getConfigure();
};

#endif //__CYCLE_HPP__
