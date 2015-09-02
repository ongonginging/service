
#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include <sys/types.h>
#include <boost/shared_ptr.hpp>

#include "Buffer.hpp"
#include "ClientSocket.hpp"

class Connection{
    private:
        std::string className = "Connection";
        Buffer input;
        Buffer output;
        boost::shared_ptr<ClientSocket> clientSocket;
    public:
        Connection();
        Connection(size_t inputBufferSize, size_t outputBufferSize);
        ~Connection();
};

#endif //__CONNECTION_HPP__

