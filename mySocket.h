//
// Created by yaron on 08/01/2020.
//

#ifndef PART2_MYSOCKET_H
#define PART2_MYSOCKET_H
#include <string>
#include <unistd.h>
#include <string.h>
#include "iostream"

#define BUFFER_SIZE 256
using namespace std;
namespace server_side {
     // the following class was created for saving the socket ID
    class mySocket {
    public:
        int socketID;
    public:
        mySocket(int id) {
            socketID = id;
        }
    };
}

#endif //PART2_MYSOCKET_H
