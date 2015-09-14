
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

class CreateConnTask: public ITask {
    private:
        std::string className = "CreateconnTask";
        std::shared_ptr<ClientSocket> client;
        std::shared_ptr<ProtoWorkThread> workThread;
        
    public:
        CreateConnTask(const std::shared_ptr<ClientSocket>& client, const std::shared_ptr<ProtoWorkThread>& workThread){
            this->client = client;
            this->workThread = workThread;
        }
        ~CreateConnTask(){
        }
        std::shared_ptr<ClientSocket> getClient(){
            return this->client;
        }
        void run(){
            LOG_ENTER_FUNC("");
            LOG_LEAVE_FUNC("");
        }
};

class CloseConnTask: public ITask {
    private:
        std::string className = "CloseConnTask";
        std::shared_ptr<ClientSocket> client;
        std::shared_ptr<ProtoWorkThread> workThread;
    public:
        CloseConnTask(const std::shared_ptr<ClientSocket>& client, const std::shared_ptr<ProtoWorkThread>& workThread){
            this->client = client;
            this->workThread = workThread;
        }
        ~CloseConnTask(){
        }
        std::shared_ptr<ClientSocket> getClient(){
            return this->client;
        }
        void run(){
            LOG_ENTER_FUNC("");
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
        void notify(EVENT event, ClientSocket*); //call by dispatch module
};

#endif //__PROTOENGINE_HPP__

