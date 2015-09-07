
#include<iostream>

#include"Configure.hpp"
#include"Log.hpp"

Configure::Configure(void){
    LOG_ENTER_FUNC("default constructor");
    LOG_LEAVE_FUNC("default constructor");
}

Configure::Configure(bool flags){
    LOG_ENTER_FUNC("bool flags");
    LOG_LEAVE_FUNC("bool flags");
}

Configure::~Configure(void){
    LOG_ENTER_FUNC("default destructor");
    LOG_LEAVE_FUNC("default destructor");
}

void Configure::set(const std::string& key, const std::string& value){
    LOG_ENTER_FUNC("");
    this->configure[key] = value;   
    LOG_LEAVE_FUNC("");
}

bool Configure::get(const std::string& key, std::string& value){
    LOG_ENTER_FUNC("");
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
    LOG_LEAVE_FUNC("")
    return rv;
}

bool Configure::parseFromConfigFile(){

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
