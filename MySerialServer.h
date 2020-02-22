//
// Created by yaron on 08/01/2020.
//

#ifndef PART2_MYSERIALSERVER_H
#define PART2_MYSERIALSERVER_H

#include <thread>
#include "Server.h"
#include "ClientHandler.h"

//using namespace server_side;
class MySerialServer: public server_side::Server {
private:
    bool stopper{};
public:
    void open(int port, ClientHandler* handler);
    void close();
};
//using namespace server_side;

#endif //PART2_MYSERIALSERVER_H
