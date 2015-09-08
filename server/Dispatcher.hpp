
#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "Cycle.hpp"
#include "Event.hpp"
#include "ClientSocket.hpp"

struct Cycle;

class Dispatcher{
    private:
        std::string className = "Dispatcher";
        std::shared_ptr<Cycle> cycle;
        /*
        std::mutex mtx;
        std::condition_variable cv;
        std::queue<std::pair<EVENT, ClientSocket*>> csEvents;
        */
    public:
        Dispatcher(const std::shared_ptr<Cycle>& cycle);
        ~Dispatcher();
        bool init();
        void serve();
        void shutdown();
        void notifyProtoEngine(const EVENT& event, const ClientSocket*&);
        void notifyServiceEngine(const EVENT& event, const std::string proto);
};

#endif //__DISPATCHER_HPP__

