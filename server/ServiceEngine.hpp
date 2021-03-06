
#ifndef __SERVICEENGINE_HPP__
#define __SERVICEENGINE_HPP__

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
#include "ServiceEventHandler.hpp"

struct Manager;
class ServiceWorkThread;
class ServiceEventHandler;

class ServiceWorkThread:public std::enable_shared_from_this<ServiceWorkThread>{
    private:
        std::string className = "ServiceWorkThread";
        std::shared_ptr<ServiceEventHandler> eventHandler;
        std::queue<std::shared_ptr<ITask>> taskQueue;
        std::shared_ptr<std::thread> thread;
        int taskCtrlChan[2];
        int threadCtrlChan[2];
        friend std::shared_ptr<ServiceEventHandler> getEventHandler(ServiceWorkThread* workThread);
    public:
        ServiceWorkThread(const std::shared_ptr<Manager>& manager);
        ~ServiceWorkThread();
        bool init();
        void serve();
        void shutdown();
        void notify(std::shared_ptr<ITask>& task); //called by engine
        std::shared_ptr<ServiceWorkThread> getSharedPtr();
        bool hasTask();
        std::shared_ptr<ITask>& getTask();
};

class ServiceEngine{
    private:
        std::string className = "ServiceEngine";
        std::shared_ptr<Manager> manager;
        std::vector<std::shared_ptr<ServiceWorkThread>> workers;
    public:
        ServiceEngine(const std::shared_ptr<Manager>& manager);
        ~ServiceEngine();
        bool init();
        void serve();
        void shutdown();
        void notifyThread(const EVENT event, const std::string proto); //call by dispatch module
};

#endif //__SERVICEENGINE_HPP__

