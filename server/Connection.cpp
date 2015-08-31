
#include "Connection.hpp"

Connection::Connection(){
    std::cout<<__func__<<" enter default constructor."<<std::endl;
    std::cout<<__func__<<" leave default constructor."<<std::endl;
}

Connection::Connection(size_t inputBufferSize, size_t outputBufferSize){
    std::cout<<__func__<<" enter 1 constructor."<<std::endl;
    this->input = Buffer(inputBufferSize);
    this->output = Buffer(outputBufferSize);
    std::cout<<__func__<<" leave 1 constructor."<<std::endl;
}

Connection::~Connection(){
    std::cout<<__func__<<" enter default destructor."<<std::endl;
    std::cout<<__func__<<" leave default destructor."<<std::endl;
}

