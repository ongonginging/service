
#include<iostream>

#include"Configure.hpp"

#if 1
Configure::Configure(void){
    std::cout<<__func__<<" default constructor."<<std::endl;
}
#endif

#if 1
Configure::Configure(bool flags){
    std::cout<<__func__<<" customer constructor."<<std::endl;
}
#endif

#if 1
Configure::~Configure(void){
    std::cout<<__func__<<" default destructor."<<std::endl;
}
#endif

void Configure::set(const std::string& key, const std::string& value){
    this->configure[key] = value;   
}

bool Configure::get(const std::string& key, std::string& value){
    bool rv = false;
    std::map<std::string, std::string>::iterator it;
    it = this->configure.find(key);
    if (it != this->configure.end()){
        value = it->second;
        rv = true;
    }else{
        value = "";
        rv = false;
    }
    return rv;
}

#if 1
Test::Test(void){
    std::cout<<__func__<<" default constructor."<<std::endl;
}
#endif

#if 1
Test::Test(bool flags){
    std::cout<<__func__<<" customer constructor."<<std::endl;
}
#endif

#if 1
Test::~Test(void){
    std::cout<<__func__<<" default destructor."<<std::endl;
}
#endif
