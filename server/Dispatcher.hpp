
#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "Manager.hpp"
#include "Event.hpp"
#include "ClientSocket.hpp"

struct Manager;

class Dispatcher{
    private:
        std::string className = "Dispatcher";
        std::shared_ptr<Manager> manager;
    public:
        Dispatcher(const std::weak_ptr<Manager>& manager);
        ~Dispatcher();
        bool init();
        void serve();
        void shutdown();
        void notifyProtoEngine(const EVENT event, const ClientSocket*);
        void notifyServiceEngine(const EVENT event, const std::string proto);
};

#endif //__DISPATCHER_HPP__

