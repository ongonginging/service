
#include <stdlib.h>
#include <iostream>

#include <sys/types.h>

#include "Buffer.hpp"

Buffer::Buffer(){
    std::cout<<__func__<<" default constructor."<<std::endl;
    this->size = 65535;
    this->ptr = NULL;
}

Buffer::Buffer(const size_t& size){
    std::cout<<__func__<<" constructor."<<std::endl;
    if (size<=512){
        std::cout<<"buffer size you set is litter than 512."<<std::endl;
        this->size = 65535;
    }else{
        this->size = size;
    }
    this->ptr = (unsigned char*)malloc(this->size); //todo: alloc from mm module
    if (this->ptr == NULL){
        std::cout<<"alloced memory failed."<<std::endl;
    }
}

Buffer::~Buffer(){
    std::cout<<__func__<<" default destructor."<<std::endl;
    if (this->ptr != NULL){
        free(this->ptr);
        this->ptr = NULL;
    }
    this->size = 0;
}

bool Buffer::read(std::string& data){
    bool rv = true;
    if (this->ptr == NULL){
        std::cout<<"buffer is not initialized."<<std::endl;
        rv = false;
    }
    return rv;
}

bool Buffer::write(const std::string& data){
    bool rv = true;
    if (this->ptr == NULL){
        std::cout<<"buffer is not initialized."<<std::endl;
        rv = false;
    }
    return rv;
}

