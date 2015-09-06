
#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "Configure.hpp"
#include "ClientSocket.hpp"

class Dispatcher{
    public:
        typedef enum EVENT{
            CREATE_CONNECTION = 0,
            DELETE_CONNECTION = 1,
            DECODE_PROTOCOL   = 2,
            ENCODE_PROTOCOL   = 3,
        }EVENT;
    private:
        std::string className = "Dispatcher";
        std::shared_ptr<Configure> configure;
        std::mutex mtx;
        std::condition_variable cv;
        std::queue<std::pair<EVENT, ClientSocket*>> csEvents;
    public:
        Dispatcher(const std::weak_ptr<Configure>& configure);
        ~Dispatcher();

        void notifyClientSocketEv(const EVENT& id, const ClientSocket*&);
        void serve(void);
};

#endif //__DISPATCHER_HPP__

