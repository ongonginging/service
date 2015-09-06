
#ifndef __CYCLE_HPP__
#define __CYCLE_HPP__

#include<memory>

#include "Configure.hpp"

class Cycle{
    private:
        std::shared_ptr<Configure> configure;
    public:
        Cycle();
        ~Cycle();
        void setConfigure(const Configure*& configure);
        std::weak_ptr<Configure> getConfigure();
};

#endif //__CYCLE_HPP__
