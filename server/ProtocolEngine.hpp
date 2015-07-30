
#ifndef __PROTOCOLENGINE_HPP__
#define __PROTOCOLENGINE_HPP__

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

#include "Configure.hpp"

class Thread{
    private:
        std::queue<int> qfd; 
        std::thread thread;
    public:
};

class ProtocolEngine{
    private:
        Thread
        Configure conf;
    public:
};

#endif //__PROTOCOLENGINE_HPP__
