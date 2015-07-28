
#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

#include<iostream>
#include<memory>

#include"Listener.hpp"

class Dispatcher{
    private:
        std::auto_ptr<Listener*> apListener;
    public:
        void serve(void);
};

#endif //__DISPATCHER_HPP__
