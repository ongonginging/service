
#ifndef __PROTOENGINE_HPP__
#define __PROTOENGINE_HPP__

#include <iostream>
#include <unordered_map>
#include <thread>

#include <boost/shared_ptr.hpp>

#include "Configure.hpp"
#include "Connection.hpp"
#include "ProtoEventHandler.hpp"

class Task{
    private:
        boost::shared_ptr<ProtoEventHandler> handler;
    public:
        void init();
        void serve();
        void shutdown();
};

class Processor{
    private:
        std::unordered_map<int, Connection> conns; // combine connection with socket
        std::thread thread;
    public:
        Processor();
        Processor(const Task& task);
        ~Processor();
};

class ProtoEngine{
    private:
        std::string className = "ProtoEngine";
        boost::shared_ptr<Configure> configure;
        std::vector<Processor> procPool;
    public:
        ProtoEngine();
        ~ProtoEngine();
        void post();
};

#endif //__PROTOENGINE_HPP__

