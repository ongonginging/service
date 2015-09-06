
#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <iostream>
#include <sstream>
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

class Logger{
    private:
        std::vector<std::string> vecOutput;
        std::string funcName;
        std::string fileName;
        int lineNum;
    public:
        Logger(const std::string& fileName, const std::string& funcName, const int& lineNum){
            this->fileName = fileName;
            this->funcName = funcName;
            this->lineNum = lineNum;
        }
        template<typename T>
        void log(T v){
            this->vecOutput.push_back(boost::lexical_cast<std::string>(v));
            std::string tmp;
            for(auto& s: this->vecOutput){
                tmp = tmp + s + " ";
            }
            std::cout<<boost::posix_time::microsec_clock::universal_time()<<" "<<this->fileName<<" "<<this->funcName<<" "<<this->lineNum<<" "<<tmp<<" "<<std::endl;
        }
        template<typename T1, typename... T2>
        void log(T1 v1, T2... v2){
            this->vecOutput.push_back(boost::lexical_cast<std::string>(v1));
            log(v2...);
        }
        ~Logger(){
        }
};

template<typename... T>
void LogFn(const std::string& fileName, const std::string& funcName, const int& lineNum, T... v){
    Logger(fileName, funcName, lineNum).log(v...);
}

#define log(v...){ \
    LogFn(__FILE__, __func__, __LINE__, v); \
}

#endif //__LOG_HPP__

