
#include "Connection.hpp"

Connection::Connection(){
    std::cout<<__func__<<" default constructor."<<std::endl;
}

Connection::Connection(size_t inputBufferSize, size_t outputBufferSize){
    std::cout<<__func__<<" customer constructor."<<std::endl;
    this->input = Buffer(inputBufferSize);
    this->output = Buffer(outputBufferSize);
}

Connection::~Connection(){
    std::cout<<__func__<<" default destructor."<<std::endl;
}

