
#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include<iostream>
#include<sys/types.h>

class Buffer{
    protected:
        size_t size;
        unsigned char* ptr;
    public:
        Buffer();
        Buffer(const size_t& size);
        ~Buffer();
        bool read(std::string& data);
        bool write(const std::string& data);
};

#endif //__BUFFER_HPP__
