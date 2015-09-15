#ifndef __ITASK_HPP__
#define __ITASK_HPP__

class ITask{
    public:
        ITask(){}
        virtual ~ITask(){}
        virtual void run()=0;
};

#endif //__ITASK_HPP__
