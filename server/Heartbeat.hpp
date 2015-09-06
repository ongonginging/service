
#ifndef __HEARTBEAT_HPP__
#define __HEARTBEAT_HPP__

#include "Configure.hpp"
#include "IEventHandler.hpp"

class Heartbeat:public IEventHandler{
    public:
        bool init(const boost::shared_ptr<Configure>& configure);
        void send();
        void shutdown();
};

#endif //__HEARTBEAT_HPP__
