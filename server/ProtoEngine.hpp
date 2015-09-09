
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

class WorkThread{
    private:
        std::string className = "WorkThread";
        std::shared_ptr<ProtoEventHandler> eventHandler;
        std::queue<std::shared_ptr<ITask>> taskQueue;
        int connCtrlChan[2];
        int threadCtrlChan[2];
        friend std::shared_ptr<ProtoEventHandler> getEventHandler(WorkThread* workThread);
    public:
        WorkThread(const std::shared_ptr<Manager>& manager);
        ~WorkThread();
        bool init();
        void serve();
        void shutdown();
        void notify(EVENT event, ClientSocket*); //called by engine

        bool hasTask();
        std::shared_ptr<ITask>& getTask();
};

class CreateConnectionTask: public ITask {
    private:
        ClientSocket* client;
        WorkThread* workThread;
    public:
        CreateConnectionTask(const ClientSocket* client, const WorkThread* workThread){
            this->client = const_cast<ClientSocket*>(client);
            this->workThread = const_cast<WorkThread*>(workThread);
        }
        ~CreateConnectionTask(){
        }
        ClientSocket* getClient(){
            return this->client;
        }
        void run(){
        }
};

class CloseConnectionTask: public ITask {
    private:
        ClientSocket* client;
        WorkThread* workThread;
    public:
        CloseConnectionTask(const ClientSocket* client, const WorkThread* workThread){
            this->client = const_cast<ClientSocket*>(client);
            this->workThread = const_cast<WorkThread*>(workThread);
        }
        ~CloseConnectionTask(){
        }
        ClientSocket* getClient(){
            return this->client;
        }
        void run(){
        }
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

