
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

#include "Log.hpp"
#include "Manager.hpp"
#include "ProtoEngine.hpp"

WorkThread::WorkThread(const std::shared_ptr<Manager>& manager){
}

WorkThread::~WorkThread(){
}

bool WorkThread::init(){
}

void WorkThread::serve(){
}

void WorkThread::shutdown(){
}

void WorkThread::notify(EVENT event, ClientSocket* data){
}

ProtoEngine::ProtoEngine(const std::shared_ptr<Manager>& manager){
    this->manager = manager;
    log("manager.use_count:",manager.use_count());
    log("this->manager.use_count:",this->manager.use_count());
}

ProtoEngine::~ProtoEngine(){

}

bool ProtoEngine::init(){
}

void ProtoEngine::serve(){
}

void ProtoEngine::shutdown(){
}

void ProtoEngine::notify(EVENT event, ClientSocket* data){
}

