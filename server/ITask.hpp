#ifndef __ITASK_HPP__
#define __ITASK_HPP__

#include "Log.hpp"

class ITask{
    private:
        std::string className = "ITask";
    public:
        ITask(){
            LOG_ENTER_FUNC("default constructor.");
            LOG_LEAVE_FUNC("default constructor.");
        }
        virtual ~ITask(){
            LOG_ENTER_FUNC("default destructor.");
            LOG_LEAVE_FUNC("default destructor.");
        }
        virtual void run()=0;
};

#endif //__ITASK_HPP__
