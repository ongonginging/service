
#ifndef __SERVICEENGINE_HPP__
#define __SERVICEENGINE_HPP__

#include <iostream>
#include <vector>
#include <thread>

#include "Manager.hpp"

struct Manager;

class ServiceEngine{
    private:
        std::string className = "ServiceEngine";
        std::shared_ptr<Manager> manager;
    public:
        ServiceEngine();
        ~ServiceEngine();
        void notify();
};

#endif //__SERVICEENGINE_HPP__

