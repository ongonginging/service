
#ifndef __HEARTBEAT_HPP__
#define __HEARTBEAT_HPP__

#include <memory>
#include "Cycle.hpp"

struct Cycle;

class Heartbeat{
    private:
        std::string className = "HeartBeat";
        struct event_base* base; 
        std::shared_ptr<Cycle> cycle;
    public:
        bool init(const std::shared_ptr<Cycle>& cycle);
        void serve();
        void shutdown();
};

#endif //__HEARTBEAT_HPP__
