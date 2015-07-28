
#include"Protocol.hpp"

int& Header::read_length(void){
    return this->length;
}

void Header::write_length(const int& length){

}

std::string& Body::read_data(void){
    return this->data;
}

void Body::write_data(const std::string& data){

}

bool Protocol::write(const char*& output_buffer){

}

bool Protocol::read( const char*& input_buffer){

}
