
#include<unistd.h>

#include<iostream>

#include"Dispatcher.hpp"
#include"Listener.hpp"
#include"Log.hpp"

void Dispatcher::serve(void){
    LOG_ENTER_FUNC("");
    while(true){
        std::cout<<"in dispatcher."<<std::endl;
        sleep(1000);
    }
    LOG_LEAVE_FUNC("");
}
