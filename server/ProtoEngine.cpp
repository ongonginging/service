
#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

#include "ProtoEngine.hpp"

Processor::Processor(const boost::shared_ptr<Configure>& configure){
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


ProtoEngine::ProtoEngine(){

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

