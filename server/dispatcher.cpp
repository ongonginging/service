
#include<unistd.h>

#include<iostream>

#include"dispatcher.h"
#include"listener.h"

void Dispatcher::service(void){
    while(true){
        std::cout<<"in dispatcher."<<std::endl;
        sleep(1000);
    }
}
