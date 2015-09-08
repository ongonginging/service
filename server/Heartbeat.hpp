
#ifndef __HEARTBEAT_HPP__
#define __HEARTBEAT_HPP__

#include <memory>
#include "Manager.hpp"

struct Manager;

class Heartbeat{
    private:
        std::string className = "HeartBeat";
        struct event_base* base; 
        std::shared_ptr<Manager> manager;
    public:
        bool init(const std::shared_ptr<Manager>& manager);
        void serve();
        void shutdown();
};

#endif //__HEARTBEAT_HPP__
