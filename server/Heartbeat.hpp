
#ifndef __HEARTBEAT_HPP__
#define __HEARTBEAT_HPP__

#include <memory>
#include "Cycle.hpp"
#include "IEventHandler.hpp"

struct Cycle;

class Heartbeat:public IEventHandler{
    private:
        std::shared_ptr<Cycle> cycle;
    public:
        bool init(const std::shared_ptr<Cycle>& cycle);
        void send();
        void shutdown();
};

#endif //__HEARTBEAT_HPP__
