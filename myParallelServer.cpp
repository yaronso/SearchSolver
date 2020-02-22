//
// Created by yaron on 12/01/2020.
//

#include <netinet/in.h>
#include "mySocket.h"
#include <thread>
#include "myParallelServer.h"

#define TIME_OUT_FIRST 300
#define TIME_OUT 300

// the following method will run in a separate thread thr client's problem handling
void sendClient(int newsockfd, ClientHandler *clientHandler) {
    ClientHandler *ch = clientHandler->getClone();
    ch->handleClient(newsockfd);
    delete ch;
    ch = nullptr;
    //clientHandler->handleClient(newsockfd);
    close(newsockfd);
}

void activateParallelClientHandler(bool *stop, int *sock, void *cli, socklen_t *clil, ClientHandler *clientHandler) {
    struct sockaddr cli1 = *((struct sockaddr *) cli);
    socklen_t clil1 = *clil;
    int sock1 = *sock;
    struct timeval tv;
    tv.tv_sec = TIME_OUT;
    tv.tv_usec = 0;
    bool optionSet = true;
    // while we should not close the Server - run the loop
    while (*(stop)) {
        int newsockfd = accept(sock1, &cli1, &clil1);
        if (newsockfd < 0) {
            std::cout << ("ERROR on accept of the PARALLEL SERVER") << std::endl;
            return;
        }
        server_side::mySocket in(newsockfd);
        // the following thread run each client in parallel - therefore we use detach in the next command
        std::thread runParallel(sendClient, newsockfd, clientHandler);
        runParallel.detach();
        // we use the following flag because we should use the setsocket command once for each socket:
        if (optionSet) {
            setsockopt(*sock, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv,
                       sizeof tv);
            optionSet = false;
        }
    }
    ::close(sock1);
}

void myParallelServer::open(int port, ClientHandler *handler) {
    int sockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cout << ("ERROR opening socket") << std::endl;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        std::cout << ("ERROR on binding") << std::endl;
    struct timeval tv;
    tv.tv_sec = TIME_OUT_FIRST;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
    listen(sockfd, 200);
    clilen = sizeof(cli_addr);
    stopper = true;
    bool *stopperPtr = &stopper;
    int *sockfdPtr = &sockfd;
    struct sockaddr_in *client_addrPtr = &cli_addr;
    socklen_t *clilenPtr = &clilen;
    // create a new thread that will run the
    std::thread runMe(activateParallelClientHandler, stopperPtr, sockfdPtr, client_addrPtr, clilenPtr, handler);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    runMe.join();
}