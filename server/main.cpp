
#include <memory>

#include "Manager.hpp"
#include "Log.hpp"

int main(int argc, char* argv[]){
    int rv = 0;
    std::shared_ptr<Manager> manager = std::make_shared<Manager>();
    bool result = manager->init();
    if(!result){
        log("initialized manager failed.");
        return -1;
    }
    manager->serve();
    return rv;
}

