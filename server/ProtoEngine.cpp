
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
#include "Cycle.hpp"
#include "ProtoEngine.hpp"

WorkThread::WorkThread(const std::shared_ptr<Cycle>& cycle){
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

ProtoEngine::ProtoEngine(const std::shared_ptr<Cycle>& cycle){
    this->cycle = cycle;
    log("cycle.use_count:",cycle.use_count());
    log("this->cycle.use_count:",this->cycle.use_count());
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

