
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
