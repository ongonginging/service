
#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <boost/date_time/posix_time/posix_time.hpp>

#define LOG_ENTER_FUNC(a) { \
        std::cout<<boost::posix_time::microsec_clock::universal_time()<<" "<<this->className<<"::"<<__func__<<" enter "<<a<<std::endl; \
}

#define LOG_LEAVE_FUNC(a)  { \
        std::cout<<boost::posix_time::microsec_clock::universal_time()<<" "<<this->className<<"::"<<__func__<<" leave "<<a<<std::endl; \
}

#define GLOBAL_LOG_ENTER_FUNC(a) { \
        std::cout<<boost::posix_time::microsec_clock::universal_time()<<" "<<__func__<<" enter "<<a<<std::endl; \
}

#define GLOBAL_LOG_LEAVE_FUNC(a)  { \
        std::cout<<boost::posix_time::microsec_clock::universal_time()<<" "<<__func__<<" leave "<<a<<std::endl; \
}

#endif //__LOG_HPP__
