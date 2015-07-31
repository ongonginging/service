
#ifndef __PROTOCOLENGINE_HPP__
#define __PROTOCOLENGINE_HPP__

#include <iostream>
#include <map>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

#include <boost/shared_ptr.hpp>

#include "Configure.hpp"
#include "Connection.hpp"

class Thread{
    private:
        std::map<int, boost::shared_ptr<Connection>> event; 
        std::thread thread;
    public:
};

class ProtocolEngine{
    private:
        boost::shared_ptr<Configure> configure;
        std::map<int, Thread> hThreadPool;//map fd to thread 
    public:
        ProtocolEngine();
        ~ProtocolEngine();
        int enter(int fd, int event);
        int entry(int fd, int event);
        int leave(int fd, int event);
};

#endif //__PROTOCOLENGINE_HPP__
