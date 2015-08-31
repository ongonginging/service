
#define LOG_ENTER_FUNC(a) { \
        std::cout<<this->className<<"::"<<__func__<<" enter "<<a<<std::endl; \
}

#define LOG_LEAVE_FUNC(a)  { \
        std::cout<<this->className<<"::"<<__func__<<" leave "<<a<<std::endl; \
}

#define GLOBAL_LOG_ENTER_FUNC(a) { \
        std::cout<<__func__<<" enter "<<a<<std::endl; \
}

#define GLOBAL_LOG_LEAVE_FUNC(a)  { \
        std::cout<<__func__<<" leave "<<a<<std::endl; \
}

