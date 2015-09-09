
#include <fcntl.h>

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
#include <boost/lexical_cast.hpp>

#include "Log.hpp"
#include "Manager.hpp"
#include "ProtoEngine.hpp"
#include "ProtoEventHandler.hpp"

std::shared_ptr<ProtoEventHandler> getEventHandler(WorkThread* workThread){
    GLOBAL_LOG_ENTER_FUNC("");
    GLOBAL_LOG_LEAVE_FUNC("");
    return workThread->eventHandler;
}

void threadCtrlCb(evutil_socket_t fd, short event, void *arg){
    GLOBAL_LOG_ENTER_FUNC("");
    //todo: figure out event is EV_READ, and no exception thrown.
    uint8_t op;
    if(-1 == read(fd, (void*)&op, 1)){
        log("failed to read channel of thread controller. errno = ", errno);
    }
    WorkThread* workThread = reinterpret_cast<WorkThread*>(arg);
    std::shared_ptr<ProtoEventHandler> eventHandler = getEventHandler(workThread);
    log("eventHandler.use_count() = ", eventHandler.use_count());
    eventHandler->shutdown();
    GLOBAL_LOG_LEAVE_FUNC("");
}

void connCtrlCb(evutil_socket_t fd, short event, void *arg){
    GLOBAL_LOG_ENTER_FUNC("");
    //todo: figure out event is EV_READ, and no exception thrown.
    uint8_t op;
    if(-1 == read(fd, (void*)&op, 1)){
        log("failed to read channel of thread controller. errno = ", errno);
    }
    WorkThread* workThread = reinterpret_cast<WorkThread*>(arg);
    if(workThread->hasTask()){
        std::shared_ptr<ITask>& task = workThread->getTask();
        log("task.use_count() = ", task.use_count());
        task->run();
    }
    GLOBAL_LOG_LEAVE_FUNC("");
}

void connReadCb(evutil_socket_t fd, short event, void *arg){
    GLOBAL_LOG_ENTER_FUNC("");
    //todo: figure out event is EV_READ, no exception thrown.
    GLOBAL_LOG_ENTER_FUNC("");
}

WorkThread::WorkThread(const std::shared_ptr<Manager>& manager){
    LOG_ENTER_FUNC("");
    if(-1 == pipe(this->threadCtrlChan)){
        log("failed to create control channel." );
        exit(1);
    }
    log("this->threadCtrlChan[0] = ", this->threadCtrlChan[0], " this->threadCtrlChan[1] = ", this->threadCtrlChan[1]);
    if(-1 == fcntl(this->threadCtrlChan[0], F_SETFL, O_NONBLOCK|fcntl(this->threadCtrlChan[0], F_GETFL))){
        log("set nonblocking to this->threadCtrlChan[0]", this->threadCtrlChan[0], "failed. errno =", errno);
        exit(1);
    }
    if(-1 == fcntl(this->threadCtrlChan[1], F_SETFL, O_NONBLOCK|fcntl(this->threadCtrlChan[1], F_GETFL))){
        log("set nonblocking to this->threadCtrlChan[1]", this->threadCtrlChan[1], "failed. errno =", errno);
        exit(1);
    }
    if(-1 == pipe(this->connCtrlChan)){
        log("failed to create connection channel." );
        exit(1);
    }
    log("this->connCtrlChan[0] = ", this->connCtrlChan[0], " this->connCtrlChan[1] = ", this->connCtrlChan[1]);
    if(-1 == fcntl(this->connCtrlChan[0], F_SETFL, O_NONBLOCK|fcntl(this->connCtrlChan[0], F_GETFL))){
        log("set nonblocking to this->connCtrlChan[0]", this->connCtrlChan[0], "failed. errno =", errno);
        exit(1);
    }
    if(-1 == fcntl(this->connCtrlChan[1], F_SETFL, O_NONBLOCK|fcntl(this->connCtrlChan[1], F_GETFL))){
        log("set nonblocking to this->connCtrlChan[1]", this->connCtrlChan[1], "failed. errno =", errno);
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
    this->eventHandler = std::make_shared<ProtoEventHandler>(
            this->connCtrlChan[0],
            this->threadCtrlChan[0],
            this->getSharedPtr(),
            connReadCb,
            connCtrlCb,
            threadCtrlCb
            );
    this->eventHandler->init();
    LOG_LEAVE_FUNC("");
}

void WorkThread::serve(){
    LOG_ENTER_FUNC("");
    std::function<void(std::shared_ptr<ProtoEventHandler>)> fn = [](std::shared_ptr<ProtoEventHandler> sp){return sp->serve();};
    this->thread = std::make_shared<std::thread>(fn, this->eventHandler);
    this->thread->detach();
    log("start protocol thread:", this->thread->get_id());
    log("this->thread.use_count() = ", this->thread.use_count());
    LOG_LEAVE_FUNC("");
}

void WorkThread::shutdown(){
    LOG_ENTER_FUNC("");
    close(this->connCtrlChan[0]);//不再接收新任务
    while(this->hasTask());//等待剩余任务处理完成
    uint8_t op = 1;
    if(write(this->threadCtrlChan[1], &op, 1) == -1){//退出线程
        log("failed to write this->threadCtrlChan[1]. errno = ", errno);
    }
    close(this->threadCtrlChan[0]);//关闭通道
    LOG_LEAVE_FUNC("");
}

void WorkThread::notify(std::shared_ptr<ITask>& task){
    LOG_ENTER_FUNC("");
    this->taskQueue.push(task);
    uint8_t op = 1;
    if(write(this->connCtrlChan[1], &op, 1)){//send signal to eventHandler.
        log("failed to write this->connCtrlChan[1]. errno = ", errno);
    }
    LOG_LEAVE_FUNC("");
}

std::shared_ptr<WorkThread> WorkThread::getSharedPtr(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
    return shared_from_this();
}

bool WorkThread::hasTask(){
    LOG_ENTER_FUNC("");
    bool rv = (!this->taskQueue.empty());
    log("thread ", std::this_thread::get_id()," has Task:", rv?"true":"false");
    LOG_LEAVE_FUNC("");
    return rv;
}

std::shared_ptr<ITask>& WorkThread::getTask(){
    LOG_ENTER_FUNC("");
    std::shared_ptr<ITask>& task = this->taskQueue.front();
    this->taskQueue.pop();
    log("thread ", std::this_thread::get_id()," get task:", task.get());
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
    int threadNum = 0;
    std::string threadNumStr;
    this->manager->getConfig("protoThreadNumber", threadNumStr);
    if(threadNumStr.size()>0){
        threadNum = boost::lexical_cast<int>(threadNumStr);
    }
    log("total number of protocol thread to start: ", threadNum);
    for(int i=0; i<threadNum; i++){
        this->workers.push_back(std::make_shared<WorkThread>(this->manager));
        this->workers.back()->init();
        this->workers.back()->serve();
    }
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


