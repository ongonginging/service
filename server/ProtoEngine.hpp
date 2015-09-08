
#ifndef __PROTOENGINE_HPP__
#define __PROTOENGINE_HPP__

#include <iostream>
#include <unordered_map>
#include <queue>
#include <thread>
#include <memory>

#include "Cycle.hpp"
#include "ClientSocket.hpp"
#include "Connection.hpp"
#include "ProtoEventHandler.hpp"

struct Cycle;

/*
class Processor{
    private:
        std::shared_ptr<ProtoEventHandler> eventHandler;
        std::unordered_map<ClientSocket*, Connection*> conns; // combine connection with socket
        int pipe[2];
    public:
        Processor(const std::shared_ptr<Cycle>& cycle);
        ~Processor();
        void notify(Event event, ClientSocket*); // called by engine
        bool init();
        void serve();
        void shutdown();
};
*/

class ProtoEngine{
    private:
        std::string className = "ProtoEngine";
        std::shared_ptr<Cycle> cycle;
        std::queue<std::pair<EVENT, ClientSocket*>> qEvent;
        //std::vector<Processor> vecProcessor;
    public:
        ProtoEngine(const std::shared_ptr<Cycle>& cycle);
        ~ProtoEngine();
        bool init();
        void serve();
        void shutdown();
        void notify(EVENT event, ClientSocket*); //call by dispatch module
};

#endif //__PROTOENGINE_HPP__

