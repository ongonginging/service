
#include<unistd.h>

#include<iostream>

#include"Dispatcher.hpp"
#include"Listener.hpp"

void Dispatcher::service(void){
    while(true){
        std::cout<<"in dispatcher."<<std::endl;
        sleep(1000);
    }
}