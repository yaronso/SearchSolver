//
// Created by yaron on 08/01/2020.
//

#ifndef PART2_SERVER_H
#define PART2_SERVER_H
#include "ClientHandler.h"
namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler *handler) = 0;
        virtual void close() = 0;
        virtual ~Server() = default;
    };
}

#endif //PART2_SERVER_H
