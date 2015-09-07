
#ifndef __PROTOENGINE_HPP__
#define __PROTOENGINE_HPP__

#include <iostream>
#include <unordered_map>
#include <queue>
#include <thread>
#include <memory>

#include "Configure.hpp"
#include "ClientSocket.hpp"
#include "Connection.hpp"
#include "ProtoEventHandler.hpp"

typedef enum ProtoEvType{
    CreateConnection,
    CloseConnection,
}ProtoEvType;

class Processor{
    private:
        std::shared_ptr<ProtoEventHandler> eventHandler;
        std::unordered_map<ClientSocket*, Connection*> conns; // combine connection with socket
        int pipe[2]; //write pointer of clientsocket to pipe. 1.add new connection; 2.close connection
    public:
        Processor(const std::shared_ptr<Configure>& configure);
        ~Processor();
        void notify(ProtoEvType event, ClientSocket*); // called by engine
        bool init();
        void serve();
        void shutdown();
};

class ProtoEngine{
    private:
        std::string className = "ProtoEngine";
        std::shared_ptr<Configure> configure;
        std::queue<std::pair<ProtoEvType, ClientSocket*>> qEvent;
        std::vector<Processor> vecProcessor;
    public:
        ProtoEngine(const std::shared_ptr<Configure>& configure);
        ~ProtoEngine();
        bool init();
        void serve();
        void shutdown();
        void notify(ProtoEvType event, ClientSocket*); //call by dispatch module
};

#endif //__PROTOENGINE_HPP__

