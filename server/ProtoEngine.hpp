
#ifndef __PROTOENGINE_HPP__
#define __PROTOENGINE_HPP__

#include <iostream>
#include <unordered_map>
#include <queue>
#include <thread>
#include <memory>

#include "ITask.hpp"
#include "Manager.hpp"
#include "ClientSocket.hpp"
#include "Connection.hpp"
#include "ProtoEventHandler.hpp"

struct Manager;

class CreateConnTask:public ITask{
    private:
        EVENT event;
        ClientSocket* cs;
    public:
        void run();
};

class CloseConnTask:public ITask{
    private:
        EVENT event;
        ClientSocket* cs;
    public:
        void run();
};

class WorkThread{
    private:
        std::string className = "WorkThread";
        std::shared_ptr<ProtoEventHandler> eventHandler;
        std::queue<std::pair<EVENT, ClientSocket*>> eventQueue;
        int connCtrlChan[2];
        int threadCtrlChan[2];
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
        std::vector<WorkThread> workThreadVec;
    public:
        ProtoEngine(const std::shared_ptr<Manager>& manager);
        ~ProtoEngine();
        bool init();
        void serve();
        void shutdown();
        void notify(EVENT event, ClientSocket*); //call by dispatch module
};

#endif //__PROTOENGINE_HPP__

