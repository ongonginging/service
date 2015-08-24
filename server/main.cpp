
#include <iostream>
#include <boost/shared_ptr.hpp>

#include"Configure.hpp"
#include"ServerSocket.hpp"
#include"Listener.hpp"

int main(int argc, char* argv[]){
    int rv = 0;
    boost::shared_ptr<Configure> spConfigure(new Test());
    spConfigure->set("port", "9544");
    spConfigure->set("host", "127.0.0.1");
    spConfigure->set("backlog", "1024");

#if 0 //test configure module
    bool result = false;
    std::string value = "";
    result = spConfigure->get("port", value);
    std::cout<<"port = "<<value<<std::endl;
    result = spConfigure->get("host", value);
    std::cout<<"host = "<<value<<std::endl;
    result = spConfigure->get("backlog", value);
    std::cout<<"backlog = "<<value<<std::endl;
    result = spConfigure->get("hello, world!", value);
    std::cout<<"hello, world = "<<value<<std::endl;
#endif 

#if 0//test configure module 
    Configure* pConfigure(new Test());
    delete(pConfigure);
#endif

    return rv;
}
