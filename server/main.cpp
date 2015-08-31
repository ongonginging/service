
#include <iostream>
#include <boost/shared_ptr.hpp>

#include"Configure.hpp"
#include"ServerSocket.hpp"
#include"Listener.hpp"

int main(int argc, char* argv[]){
    int rv = 0;
    boost::shared_ptr<Configure> configure(new Configure());
    configure->set("port", "9544");
    configure->set("host", "127.0.0.1");
    configure->set("backlog", "1024");
    Listener listener = Listener(configure);
    listener.init();
    listener.serve();
    listener.shutdown();

#if 0 //test configure module
    bool result = false;
    std::string value = "";
    result = configure->get("port", value);
    std::cout<<"port = "<<value<<std::endl;
    result = configure->get("host", value);
    std::cout<<"host = "<<value<<std::endl;
    result = configure->get("backlog", value);
    std::cout<<"backlog = "<<value<<std::endl;
    result = configure->get("hello, world!", value);
    std::cout<<"hello, world = "<<value<<std::endl;
#endif 

#if 0//test configure module 
    Configure* pConfigure(new Test());
    delete(pConfigure);
#endif

    return rv;
}

