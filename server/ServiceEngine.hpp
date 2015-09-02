
#ifndef __SERVICEENGINE_HPP__
#define __SERVICEENGINE_HPP__

#include <thread>

class ServiceEngine{
    private:
        std::string className = "ServiceEngine";
        std::vector<std::thread> threadPool;
    public:
        ServiceEngine();
        ~ServiceEngine();
        void post();
};

#endif //__SERVICEENGINE_HPP__

