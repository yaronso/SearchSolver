//
// Created by yaron on 12/01/2020.
//

#ifndef PART2_MYPARALLELSERVER_H
#define PART2_MYPARALLELSERVER_H
#include "mySocket.h"
#include "Server.h"

using namespace server_side;
class myParallelServer : public Server {
private:
    bool stopper;
public:
    void open(int port, ClientHandler* handler) override ;
    void close() override {
        stopper = false;
    }
};

#endif //PART2_MYPARALLELSERVER_H
