
#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

#include<iostream>

#include<boost/shared_ptr.hpp>
#include<boost/weak_ptr.hpp>

#include"Listener.hpp"
#include"Configure.hpp"

class Dispatcher{
    private:
        boost::shared_ptr<Configure> spConfigure;
        boost::shared_ptr<Listener> spListener;
    public:
        void serve(void);
};

#endif //__DISPATCHER_HPP__
