
#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include<map>
#include<iostream>

class Configure{
    private:
        std::string className = "Configure";
        std::map<std::string, std::string> configure;
    public:
        Configure();
        Configure(bool flags);
#if 1
        ~Configure(void);
#else
        virtual ~Configure();
#endif
        void set(const std::string& key, const std::string& value);
        bool get(const std::string& key, std::string& value);
};

class Test:public Configure{
    private:
    public:
        Test();
        Test(bool flags);
        ~Test();
};

#endif //__CONFIG_HPP__

