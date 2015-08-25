
#include<unistd.h>

#include<iostream>

#include"Dispatcher.hpp"
#include"Listenner.hpp"

void Dispatcher::serve(void){
    while(true){
        std::cout<<"in dispatcher."<<std::endl;
        sleep(1000);
    }
}
