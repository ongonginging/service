
#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include<sys/types.h>

#include"Buffer.hpp"

class Connection{
    private:
        std::string className = "Connection";
        Buffer input;
        Buffer output;
    public:
        Connection();
        Connection(size_t inputBufferSize, size_t outputBufferSize);
        ~Connection();
};

#endif //__CONNECTION_HPP__

