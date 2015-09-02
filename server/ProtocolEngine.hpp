
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

class ProtocolEngine{
    private:
        std::string className = "ProtocolEngine";
        boost::shared_ptr<Configure> configure;
        std::vector<std::thread> threadPool;
    public:
        ProtocolEngine();
        ~ProtocolEngine();
        void post();
};

#endif //__PROTOCOLENGINE_HPP__
