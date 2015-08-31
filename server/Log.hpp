
#define LOG_ENTER_FUNC(a) { \
        std::cout<<this->className<<"::"<<__func__<<" enter "<<a<<std::endl; \
}

#define LOG_LEAVE_FUNC(a)  { \
        std::cout<<this->className<<"::"<<__func__<<" leave "<<a<<std::endl; \
}
