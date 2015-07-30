
#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include<map>
#include<iostream>

class Configure{
    private:
        std::map<std::string, std::string> configure;
    public:
        void set(const std::string& key, const std::string& value);
        std::string& get(const std::string& key);
};

#endif //__CONFIG_HPP__
