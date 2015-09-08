
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
/*
Processor::Processor(const std::shared_ptr<Cycle>& cycle){
}

Processor::~Processor(){
}

bool Processor::init(){
}

void Processor::serve(){
}

void Processor::shutdown(){
}

void Processor::notify(EVENT event, ClientSocket* data){
}

*/

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

