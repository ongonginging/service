
#ifndef __PROTOENGINE_HPP__
#define __PROTOENGINE_HPP__

#include <iostream>
#include <unordered_map>
#include <queue>
#include <thread>
#include <memory>

#include "Manager.hpp"
#include "ClientSocket.hpp"
#include "Connection.hpp"
#include "ProtoEventHandler.hpp"

struct Manager;

class WorkThread{
    private:
        std::shared_ptr<ProtoEventHandler> eventHandler;
        std::unordered_map<ClientSocket*, Connection*> conns; // combine connection with socket
        int pipe[2];
    public:
        WorkThread(const std::shared_ptr<Manager>& manager);
        ~WorkThread();
        void notify(EVENT event, ClientSocket*); // called by engine
        bool init();
        void serve();
        void shutdown();
};

class ProtoEngine{
    private:
        std::string className = "ProtoEngine";
        std::shared_ptr<Manager> manager;
        std::vector<WorkThread> workers;
    public:
        ProtoEngine(const std::shared_ptr<Manager>& manager);
        ~ProtoEngine();
        bool init();
        void serve();
        void shutdown();
        void notify(EVENT event, ClientSocket*); //call by dispatch module
};

#endif //__PROTOENGINE_HPP__

