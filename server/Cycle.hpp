
#ifndef __CYCLE_HPP__
#define __CYCLE_HPP__

#include <memory>

#include "Configure.hpp"
#include "Listener.hpp"
#include "Dispatcher.hpp"
#include "ProtoEngine.hpp"
#include "ServiceEngine.hpp"

class Listener;
class Configure;
class Dispatcher;
class ProtoEngine;
class ServiceEngine;

struct Cycle{
    public:
        std::shared_ptr<Configure> configure;
        std::shared_ptr<Dispatcher> dispatcher;
        std::shared_ptr<Listener> listener;
        std::shared_ptr<ProtoEngine> protoEngine;
        std::shared_ptr<ServiceEngine> serviceEngine;

        Cycle();
        ~Cycle();
        void serve();
        bool getConfig(const std::string& key, std::string& value);
};

#endif //__CYCLE_HPP__

