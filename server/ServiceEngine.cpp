
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
#include "ServiceEngine.hpp"
#include "ServiceEventHandler.hpp"

std::shared_ptr<ServiceEventHandler> getEventHandler(ServiceWorkThread* workThread){
    GLOBAL_LOG_ENTER_FUNC("");
    GLOBAL_LOG_LEAVE_FUNC("");
    return workThread->eventHandler;
}

static void threadCtrlCb(evutil_socket_t fd, short event, void *arg){
    GLOBAL_LOG_ENTER_FUNC("");
    //todo: figure out event is EV_READ, and no exception thrown.
    uint8_t op;
    while(-1 != read(fd, (void*)&op, 1)){}
    ServiceWorkThread* workThread = reinterpret_cast<ServiceWorkThread*>(arg);
    std::shared_ptr<ServiceEventHandler> eventHandler = getEventHandler(workThread);
    log("eventHandler.use_count() = ", eventHandler.use_count());
    eventHandler->shutdown();
    GLOBAL_LOG_LEAVE_FUNC("");
}

void taskCtrlCb(evutil_socket_t fd, short event, void *arg){
    GLOBAL_LOG_ENTER_FUNC("");
    //todo: figure out event is EV_READ, and no exception thrown.
    uint8_t op;
    while(-1 != read(fd, (void*)&op, 1)){}
    ServiceWorkThread* workThread = reinterpret_cast<ServiceWorkThread*>(arg);
    while(workThread->hasTask()){
        std::shared_ptr<ITask>& task = workThread->getTask();
        log("task.use_count() = ", task.use_count());
        task->run();
    }
    GLOBAL_LOG_LEAVE_FUNC("");
}

ServiceWorkThread::ServiceWorkThread(const std::shared_ptr<Manager>& manager){
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
    if(-1 == pipe(this->taskCtrlChan)){
        log("failed to create connection channel." );
        exit(1);
    }
    log("this->taskCtrlChan[0] = ", this->taskCtrlChan[0], " this->taskCtrlChan[1] = ", this->taskCtrlChan[1]);
    if(-1 == fcntl(this->taskCtrlChan[0], F_SETFL, O_NONBLOCK|fcntl(this->taskCtrlChan[0], F_GETFL))){
        log("set nonblocking to this->taskCtrlChan[0]", this->taskCtrlChan[0], "failed. errno =", errno);
        exit(1);
    }
    if(-1 == fcntl(this->taskCtrlChan[1], F_SETFL, O_NONBLOCK|fcntl(this->taskCtrlChan[1], F_GETFL))){
        log("set nonblocking to this->taskCtrlChan[1]", this->taskCtrlChan[1], "failed. errno =", errno);
        exit(1);
    } 
    LOG_LEAVE_FUNC("");
}

ServiceWorkThread::~ServiceWorkThread(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

bool ServiceWorkThread::init(){
    bool rv = true;
    LOG_ENTER_FUNC("");
    this->eventHandler = std::make_shared<ServiceEventHandler>(
            this->taskCtrlChan[0],
            this->threadCtrlChan[0],
            this->getSharedPtr(),
            taskCtrlCb,
            threadCtrlCb
            );
    rv = this->eventHandler->init();
    LOG_LEAVE_FUNC("");
    return rv;
}

void ServiceWorkThread::serve(){
    LOG_ENTER_FUNC("");
    std::function<void(std::shared_ptr<ServiceEventHandler>)> fn = [](std::shared_ptr<ServiceEventHandler> sp){return sp->serve();};
    try{
        this->thread = std::make_shared<std::thread>(fn, this->eventHandler);
        this->thread->detach();
        log("start service thread:", this->thread->get_id());
        log("this->thread.use_count() = ", this->thread.use_count());
    }catch(std::exception& e){
        log("exception info:", e.what());
    }
    LOG_LEAVE_FUNC("");
}

void ServiceWorkThread::shutdown(){
    LOG_ENTER_FUNC("");
    close(this->taskCtrlChan[0]);//不再接收新任务
    while(this->hasTask());//等待剩余任务处理完成
    uint8_t op = 1;
    if(write(this->threadCtrlChan[1], &op, 1) == -1){//退出线程
        log("failed to write this->threadCtrlChan[1]. errno = ", errno);
    }
    close(this->threadCtrlChan[0]);//关闭通道
    LOG_LEAVE_FUNC("");
}

void ServiceWorkThread::notify(std::shared_ptr<ITask>& task){
    LOG_ENTER_FUNC("");
    this->taskQueue.push(task);
    uint8_t op = 1;
    if(write(this->taskCtrlChan[1], &op, 1)){//send signal to eventHandler.
        log("failed to write this->taskCtrlChan[1]. errno = ", errno);
    }
    LOG_LEAVE_FUNC("");
}

std::shared_ptr<ServiceWorkThread> ServiceWorkThread::getSharedPtr(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
    return shared_from_this();
}

bool ServiceWorkThread::hasTask(){
    LOG_ENTER_FUNC("");
    bool rv = (!this->taskQueue.empty());
    log("thread ", std::this_thread::get_id()," has Task:", rv?"true":"false");
    LOG_LEAVE_FUNC("");
    return rv;
}

std::shared_ptr<ITask>& ServiceWorkThread::getTask(){
    LOG_ENTER_FUNC("");
    std::shared_ptr<ITask>& task = this->taskQueue.front();
    this->taskQueue.pop();
    log("thread ", std::this_thread::get_id()," get task:", task.get());
    LOG_LEAVE_FUNC("");
    return task;
}

ServiceEngine::ServiceEngine(const std::shared_ptr<Manager>& manager){
    LOG_ENTER_FUNC("");
    this->manager = manager;
    log("manager.use_count:",manager.use_count());
    log("this->manager.use_count:",this->manager.use_count());
    LOG_LEAVE_FUNC("");
}

ServiceEngine::~ServiceEngine(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

bool ServiceEngine::init(){
    LOG_ENTER_FUNC("");
    bool rv = true;
    LOG_LEAVE_FUNC("");
    return rv;
}

void ServiceEngine::serve(){
    LOG_ENTER_FUNC("");
    int threadNum = 0;
    std::string threadNumStr;
    this->manager->getConfig("serviceThreadNumber", threadNumStr);
    if(threadNumStr.size()>0){
        threadNum = boost::lexical_cast<int>(threadNumStr);
    }
    log("total number of service thread to start: ", threadNum);
    for(int i=0; i<threadNum; i++){
        this->workers.push_back(std::make_shared<ServiceWorkThread>(this->manager));
        bool result = this->workers.back()->init();
        if(!result){log("initialized service thread ", i,"failed.");}
        this->workers.back()->serve();
    }
    LOG_LEAVE_FUNC("");
}

void ServiceEngine::shutdown(){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

void ServiceEngine::notify(EVENT event, ClientSocket* data){
    LOG_ENTER_FUNC("");
    LOG_LEAVE_FUNC("");
}

