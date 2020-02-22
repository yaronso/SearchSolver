//
// Created by yaron on 08/01/2020.
//

#ifndef PART2_CLIENTHANDLER_H
#define PART2_CLIENTHANDLER_H

#include "mySocket.h"
#include "iostream"
using namespace std;
class ClientHandler {
public:
    // in will be the input client/socket problem, out - will be the solution for his problem
    //virtual int handleClient(server_side:: mySocket in, server_side:: mySocket out) = 0;
    virtual void handleClient(int socket) = 0;
    virtual  ~ClientHandler() = default;
    virtual ClientHandler* getClone()=0;

};


#endif //PART2_CLIENTHANDLER_H
