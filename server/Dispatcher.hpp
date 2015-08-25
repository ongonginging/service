
#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

#include<iostream>

#include<boost/shared_ptr.hpp>
#include<boost/weak_ptr.hpp>

#include"Listenner.hpp"
#include"Configure.hpp"

class Dispatcher{
    private:
        boost::shared_ptr<Configure> configure;
        boost::shared_ptr<Listener> listener;
    public:
        void serve(void);
};

#endif //__DISPATCHER_HPP__
