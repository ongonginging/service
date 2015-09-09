
#include <map>
#include <thread>
#include <chrono>
#include <atomic>
#include <memory>
#include <utility>
#include <iostream>
#include <functional>
#include <unordered_map>

#include <event.h>

#include "Log.hpp"
#include "Manager.hpp"
#include "ProtoEngine.hpp"
#include "ProtoEventHandler.hpp"

std::shared_ptr<ProtoEventHandler> getEventHandler(WorkThread* workThread){
    return workThread->eventHandler;
}

void threadCtrlCb(evutil_socket_t fd, short event, void *arg){
    //todo: figure out event is EV_READ, and no exception thrown.
    WorkThread* workThread = reinterpret_cast<WorkThread*>(arg);  
    std::shared_ptr<ProtoEventHandler> eventHandler = getEventHandler(workThread);
    eventHandler->shutdown();
}

void connCtrlCb(evutil_socket_t fd, short event, void *arg){
    //todo: figure out event is EV_READ, and no exception thrown.
    WorkThread* workThread = reinterpret_cast<WorkThread*>(arg);
    if(workThread->hasTask()){
        std::shared_ptr<ITask>& task = workThread->getTask();
        log("task.use_count() = ", task.use_count());
        task->run();
    }
}

void connReadCb(evutil_socket_t fd, short event, void *arg){
    //todo: figure out event is EV_READ, no exception thrown.
}

WorkThread::WorkThread(const std::shared_ptr<Manager>& manager){
    LOG_ENTER_FUNC("");
    if(-1 == pipe(this->threadCtrlChan)){
        log("failed to create control channel." );
        exit(1);
    }
    if(-1 == pipe(this->connCtrlChan)){
        log("failed to create connection channel." );
        exit(1);
    }
    LOG_LEAVE_FUNC("");
}

WorkThread::~WorkThread(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

bool WorkThread::init(){
    LOG_ENTER_FUNC("");
    this->eventHandler->init();
    LOG_LEAVE_FUNC("");
}

void WorkThread::serve(){
    LOG_ENTER_FUNC("");
    this->eventHandler->serve();
    LOG_LEAVE_FUNC("");
}

void WorkThread::shutdown(){
    LOG_ENTER_FUNC("");
    uint8_t op = 1;//shutdown eventHandler.
    if(write(this->threadCtrlChan[0], &op, 1) == -1){
        log("failed to write this->threadCtrlChan[0]. errno = ", errno);
    }
    close(this->threadCtrlChan[0]);
    close(this->connCtrlChan[0]);
    LOG_LEAVE_FUNC("");
}

void WorkThread::notify(std::shared_ptr<ITask>& task){
    LOG_ENTER_FUNC("");
    this->taskQueue.push(task);
    int8_t op = 1;
    if(write(this->connCtrlChan[0],&op, 1))//send signal to eventHandler.
    LOG_LEAVE_FUNC("");
}

std::shared_ptr<WorkThread> WorkThread::getSharedPtr(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
    return shared_from_this();
}

bool WorkThread::hasTask(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
    return (!this->taskQueue.empty());
}

std::shared_ptr<ITask>& WorkThread::getTask(){
    LOG_ENTER_FUNC("");
    std::shared_ptr<ITask>& task = this->taskQueue.front();
    this->taskQueue.pop();
    LOG_LEAVE_FUNC("");
    return task;
}

ProtoEngine::ProtoEngine(const std::shared_ptr<Manager>& manager){
    LOG_ENTER_FUNC("");
    this->manager = manager;
    log("manager.use_count:",manager.use_count());
    log("this->manager.use_count:",this->manager.use_count());
    LOG_LEAVE_FUNC("");
}

ProtoEngine::~ProtoEngine(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

bool ProtoEngine::init(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

void ProtoEngine::serve(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

void ProtoEngine::shutdown(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

void ProtoEngine::notify(EVENT event, ClientSocket* data){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}


