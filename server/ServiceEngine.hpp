
#ifndef __SERVICEENGINE_HPP__
#define __SERVICEENGINE_HPP__

#include <iostream>
#include <vector>
#include <thread>

#include "Cycle.hpp"

struct Cycle;

class ServiceEngine{
    private:
        std::string className = "ServiceEngine";
        std::shared_ptr<Cycle> cycle;
    public:
        ServiceEngine();
        ~ServiceEngine();
        void post();
};

#endif //__SERVICEENGINE_HPP__

