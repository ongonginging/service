
#include<iostream>

#include"Listener.hpp"

//#include<auto_ptr.h>

class Dispatcher{
    private:
        //std::auto_ptr<Listener> pListener;
        Listener* pListener;
    public:
        void service(void);
};
