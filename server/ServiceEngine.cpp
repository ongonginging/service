
#include <iostream>
#include <unordered_map>
#include <queue>
#include <thread>
#include <vector>
#include <memory>

#include "Log.hpp"
#include "ITask.hpp"
#include "IProtocol.hpp"
#include "Manager.hpp"
#include "ClientSocket.hpp"

/*
   std::string className = "ServiceWorkThread";
   std::queue<std::shared_ptr<ITask>> taskQueue;
   std::shared_ptr<std::thread> thread;""
 */

ServiceWorkThread::ServiceWorkThread(const std::shared_ptr<Manager>& manager){
}

ServiceWorkThread::~ServiceWorkThread(){

}

bool ServiceWorkThread::init(){

}

void ServiceWorkThread::serve(){

}

void ServiceWorkThread::shutdown(){

}

void ServiceWorkThread::notify(std::shared_ptr<ITask>& task){

}

std::shared_ptr<ServiceWorkThread> ServiceWorkThread::getSharedPtr(){

}

bool ServiceWorkThread::hasTask(){

}

std::shared_ptr<ITask>& ServiceWorkThread::getTask(){

}

/*
   std::string className = "ServiceEngine";
   std::shared_ptr<Manager> manager;
   std::vector<std::shared_ptr<ServiceWorkThread>> workers;""
   */

ServiceEngine::ServiceEngine(){

}

ServiceEngine::ServiceEngine(const std::shared_ptr<Manager>& manager){

}

ServiceEngine::~ServiceEngine(){

}

bool ServiceEngine::init(){

}

void ServiceEngine::serve(){

}

void ServiceEngine::shutdown(){

}

void ServiceEngine::notify(const IProtocol& protocol){

}
