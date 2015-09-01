
#include <iostream>
#include <boost/shared_ptr.hpp>

#include"Configure.hpp"
#include"ServerSocket.hpp"
#include"Listener.hpp"

int main(int argc, char* argv[]){
    int rv = 0;
    boost::shared_ptr<Configure> configure(new Configure());
    configure->set("port", "9544");
    configure->set("host", "0.0.0.0");
    configure->set("backlog", "1024");
    Listener listener = Listener(configure);
    listener.init();
    listener.serve();
    listener.shutdown();
    return rv;
}

