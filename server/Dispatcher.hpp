
#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "Listener.hpp"
#include "Configure.hpp"

class Dispatcher{
    private:
        std::string className = "Dispatcher";
        boost::shared_ptr<Configure> configure;
    public:
        typedef enum EVENT{
            NEW_CLIENT_SOCKET,
            NEW_PROTOCOL,
        }EVENT;
        void post(EVENT event, long data);
        void serve(void);
};

#endif //__DISPATCHER_HPP__

