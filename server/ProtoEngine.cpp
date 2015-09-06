
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
#include "ProtoEngine.hpp"

Processor::Processor(const std::shared_ptr<Configure>& configure){
}

Processor::~Processor(){
}

bool Processor::init(){
}

void Processor::serve(){
}

void Processor::shutdown(){
}

void Processor::notify(ProtoEvType event, ClientSocket* data){
}

ProtoEngine::ProtoEngine(const std::shared_ptr<Configure>& configure){

    std::weak_ptr<Configure>wp(configure);
    if(wp.expired()){
        exit(1);
    }
    this->configure = wp.lock();
    log("configure.use_count:",configure.use_count());
    log("wp.use_count:",wp.use_count());
    log("this->configure.use_count:",this->configure.use_count());
}

ProtoEngine::~ProtoEngine(){

}

bool ProtoEngine::init(){
}

void ProtoEngine::serve(){
}

void ProtoEngine::shutdown(){
}

void ProtoEngine::notify(ProtoEvType event, ClientSocket* data){
}

