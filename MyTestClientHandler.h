//
// Created by adi on 08/01/2020.
//
#include "mySocket.h"
#include <string>
#include "Solver.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "ClientHandler.h"
#include "CacheManager.h"
#include <sys/socket.h>
//#include "hash_map"


#ifndef PART2_MYTESTCLIENTHANDLER_H
#define PART2_MYTESTCLIENTHANDLER_H
template<class P, class S>
class MyTestClientHandler : public ClientHandler {
private:
    Solver<P, S> *solver;
    CacheManager<S> *cacheManager{};
public:
    MyTestClientHandler(Solver<P, S> *sol, CacheManager<S> *cache) {
        this->solver = sol;
        this->cacheManager = cache;
    }

    void handleClient(int client_socket) override {
        bool inFile = true;
        string firstBuffer = "";
        //while we didnt read the line "end"
        while (inFile) {
            //we will read chunks of data from the client
            // and split it to lines by \n
            char buffer[1024] = {0};
            read(client_socket, buffer, 1024);
            string secondBuffer = buffer;
            firstBuffer = firstBuffer + secondBuffer;
            string firstPart = firstBuffer.substr(0, firstBuffer.find("\n")); //all tha values from start to \n
            int startSecondPart = firstBuffer.find("\n") + 1;
            string secondPart = firstBuffer.substr(
                    startSecondPart, firstBuffer.length()); //all the values from \n to end
            //create string hash to the problem
            //in our case the string is one-to-one function
            string hashProblem = firstPart;

            if (firstPart == "end") {
                //we finish the reading of the file
                inFile = false;
            }

            //if we already solve this problem
            else if (this->cacheManager->find(firstPart)) {
                string solution = this->cacheManager->get(firstPart);
                const char *solutionChar = solution.c_str();
                send(client_socket, solutionChar, solution.size(), 0);
            } else {
                //if we need to solve the problem now
                string solution = this->solver->solve(firstPart);
                this->cacheManager->save(firstPart, solution);
                const char *solutionChar = solution.c_str();
                send(client_socket, solutionChar, solution.size(), 0);
            }
            //in the next iteration we will handle the secondPart after the \n
            firstBuffer = secondPart;

        }
    }
};


#endif //PART2_MYTESTCLIENTHANDLER_H
