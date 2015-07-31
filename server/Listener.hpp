
#ifndef __LISTENER_HPP__
#define __LISTENER_HPP__

#include<iostream>

#include <boost/shared_ptr.hpp>

#include"Configure.hpp"
#include"ServerSocket.hpp"

class Listener{
    private:
        boost::shared_ptr<Configure> spConfigure;
        boost::shared_ptr<ServerSocket> spServerSocket;
    public:
        Listener(void);
        Listener(const boost::shared_ptr<Configure>& spConfigure, const boost::shared_ptr<ServerSocket>& spServerSocket);
        ~Listener(void);
        void serve(void);
};

#endif //__LISTENER_HPP__
