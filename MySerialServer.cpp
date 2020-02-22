//
// Created by yaron on 08/01/2020.
//
#include "MySerialServer.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "mySocket.h"
#define TIME_OUT_FIRST 30
#define TIME_OUT 10

using namespace std;
// the following method will activate the client handler over the current connected client
void activateClientHandler(bool* stop, int* sock,void* cli, socklen_t* clil, ClientHandler* clientHandler) {
    struct sockaddr cli1 = *((struct sockaddr*) cli);
    socklen_t clil1 = *clil;
    int sock1 = *sock;
    struct timeval tv;
    tv.tv_sec = TIME_OUT;
    tv.tv_usec = 0;
    // while we should not close the Server - run the loop
    while(*(stop)) {
        // try to accpet
        int newsockfd = accept(sock1, (struct sockaddr *)&cli1, &clil1);
        if(newsockfd < 0) {
            std::cout << ("ERROR on accept, the TIME IS OUT") << std::endl;
            return;
        }
        // if the a new socket was accepted we send it to the
        server_side::mySocket in(newsockfd);
        // calling the client handler
        cout << "acceptClient" << endl;
        clientHandler->handleClient(newsockfd);
        cout << "end with client" << endl;
        ::close(newsockfd);
        setsockopt(*sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    }
    close(sock1);
}


void MySerialServer::open(int port, ClientHandler* handler) {
    int sockfd;
    socklen_t clilen;
    struct sockaddr_in  cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd ==-1 ) {
        std::cout << ("ERROR opening socket") << std::endl;
    }
    // verify all the data is zero at the beginning
    //bzero((char *) &serv_addr, sizeof(serv_addr));
    // set the fields of sockaddr_in struct
    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    // binding stage:
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) ==-1 )
        std::cout << ("ERROR on binding") << std::endl ;
    // create a struct for the timeout of the client's waiting
    struct timeval tv;
    tv.tv_sec = TIME_OUT_FIRST;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    stopper = true;
    bool* stopperPtr = &stopper;
    int* sockfdPtr = &sockfd;
    struct sockaddr_in* client_addrPtr = &cli_addr;
    socklen_t* clilenPtr = &clilen;
    // create a new thread that will run the
    std::thread runMe(activateClientHandler , stopperPtr, sockfdPtr, client_addrPtr, clilenPtr, handler);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    runMe.join();
}

void MySerialServer::close() {
    stopper = false;
}

