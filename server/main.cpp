
#include <iostream>
#include <boost/shared_ptr.hpp>

#include"Configure.hpp"

int main(int argc, char* argv[]){
    int rv = 0;
    boost::shared_ptr<Configure> spConfigure(new Test());
    //Configure* pConfigure(new Test());
    //delete(pConfigure);

    return rv;
}
