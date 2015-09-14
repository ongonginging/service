
#ifndef __PROTOENGINE_HPP__
#define __PROTOENGINE_HPP__

#include <iostream>
#include <unordered_map>
#include <queue>
#include <thread>
#include <vector>
#include <memory>

#include "Log.hpp"
#include "ITask.hpp"
#include "Manager.hpp"
#include "ClientSocket.hpp"
#include "Connection.hpp"
#include "ProtoEventHandler.hpp"

struct Manager;
class ProtoWorkThread;
class ProtoEventHandler;

class ConnCreateTask: public ITask {
    private:
        std::string className = "ConnCreateTask";
        std::shared_ptr<ClientSocket> client;
        std::shared_ptr<ProtoWorkThread> workThread;
        
    public:
        ConnCreateTask(ClientSocket* client, const std::shared_ptr<ProtoWorkThread>& workThread){
            this->client = std::shared_ptr<ClientSocket>(client);
            this->workThread = workThread;
        }
        ~ConnCreateTask(){
        }
        std::shared_ptr<ClientSocket> getClient(){
            return this->client;
        }
        void run(){
            LOG_ENTER_FUNC("");
            log("do connection creating task.");
            LOG_LEAVE_FUNC("");
        }
};

class ConnCloseTask: public ITask {
    private:
        std::string className = "ConnCloseTask";
        std::shared_ptr<ClientSocket> client;
        std::shared_ptr<ProtoWorkThread> workThread;
    public:
        ConnCloseTask(ClientSocket* client, const std::shared_ptr<ProtoWorkThread>& workThread){
            this->client = std::shared_ptr<ClientSocket>(client);
            this->workThread = workThread;
        }
        ~ConnCloseTask(){
        }
        std::shared_ptr<ClientSocket> getClient(){
            return this->client;
        }
        void run(){
            LOG_ENTER_FUNC("");
            log("do connection closing task.");
            LOG_LEAVE_FUNC("");
        }
};

class ProtoWorkThread:public std::enable_shared_from_this<ProtoWorkThread>{
    private:
        std::string className = "ProtoWorkThread";
        std::shared_ptr<ProtoEventHandler> eventHandler;
        std::queue<std::shared_ptr<ITask>> taskQueue;
        std::shared_ptr<std::thread> thread;
        int connCtrlChan[2];
        int threadCtrlChan[2];
        friend std::shared_ptr<ProtoEventHandler> getEventHandler(ProtoWorkThread* workThread);
    public:
        ProtoWorkThread(const std::shared_ptr<Manager>& manager);
        ~ProtoWorkThread();
        bool init();
        void serve();
        void shutdown();
        void notify(std::shared_ptr<ITask>& task); //called by engine
        std::shared_ptr<ProtoWorkThread> getSharedPtr();
        bool hasTask();
        std::shared_ptr<ITask>& getTask();
};

class ProtoEngine{
    private:
        std::string className = "ProtoEngine";
        std::shared_ptr<Manager> manager;
        std::vector<std::shared_ptr<ProtoWorkThread>> workers;
    public:
        ProtoEngine(const std::shared_ptr<Manager>& manager);
        ~ProtoEngine();
        bool init();
        void serve();
        void shutdown();
        void notifyThread(const EVENT event, ClientSocket*); //call by dispatch module
};

#endif //__PROTOENGINE_HPP__

