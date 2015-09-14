
#ifndef __CONFIGURE_HPP__
#define __CONFIGURE_HPP__

#include <map>
#include <memory>
#include <iostream>

class Configure{
    private:
        std::string className = "Configure";
        std::string configFile;
        std::map<std::string, std::string> configure;
    public:
        Configure();
        Configure(bool flags);
        Configure(std::string& configFile);
#if 1
        ~Configure(void);
#else
        virtual ~Configure();
#endif
        void set(const std::string& key, const std::string& value);
        bool get(const std::string& key, std::string& value);
        bool parseFromConfigFile();
};

class Test:public Configure{
    private:
    public:
        Test();
        Test(bool flags);
        ~Test();
};

#endif //__CONFIGURE_HPP__

