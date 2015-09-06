
#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include <iostream>
#include <memory>

#include <sys/types.h>

#include "Buffer.hpp"
#include "ClientSocket.hpp"

class Connection{
    private:
        std::string className = "Connection";
        Buffer input;
        Buffer output;
        std::shared_ptr<ClientSocket> clientSocket;
    public:
        Connection();
        Connection(size_t inputBufferSize, size_t outputBufferSize);
        ~Connection();
};

#endif //__CONNECTION_HPP__

