//
// Created by adi on 12/01/2020.
//

#ifndef PART2_MYCLIENTHANDLER_H
#define PART2_MYCLIENTHANDLER_H
#include <vector>
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <algorithm>
#include <sstream>
#include <sys/socket.h>
#include "MatrixProblem.h"
#include "MatrixSolverBestFS.h"
#include "BestFirstSearch.h"
#include "ISearchable.h"


class MyClientHandler : public ClientHandler {
private:
    Solver<MatrixProblem, string> *solver;
    CacheManager<string> *cacheManager{};
public:
    MyClientHandler(CacheManager<string> *cache) {
        this->cacheManager = cache;
    }



    //the client will send the matrix row by row
    //we will read the matrix as strings and insert it to matrixProblem
    //after the matrix we will gate the initial theState and goal theState
    //at the end the client will sent the word "end"
    virtual ClientHandler* getClone(){
        return new MyClientHandler(cacheManager);
    }

    void handleClient(int client_socket) override {


        vector<string> matrixStringVector;
        pair<int, int> startLocation;
        pair<int, int> goalLocation;
        int matrixRow = 0;
        int matrixCol = 0;
        bool inFile = true;
        string firstBuffer = "";
        int index = 0;
        //while we didnt read the line "end"

        while (inFile) {
            //we will read chunks of data from the client
            // and split it to lines by \n
            char buffer[1024] = {0};
            if (firstBuffer.find("end\n") == string::npos) {
                read(client_socket, buffer, 1024);
            }
            string secondBuffer = buffer;
            firstBuffer = firstBuffer + secondBuffer;
            const string firstPart = firstBuffer.substr(0, firstBuffer.find("\n")); //all tha values from start to \n
            int startSecondPart = firstBuffer.find("\n") + 1;
            string secondPart = firstBuffer.substr(
                    startSecondPart, firstBuffer.length()); //all the values from \n to end
            string currentLine = firstPart;

            //if we finish read the file
            if (firstPart == "end") {
                //we finish the reading of the file
                inFile = false;
            }
                //we are steal need to read the file
            else {
                //if its the first line we read we will count the column in the matrix by the ","
                if (matrixRow == 0) {
                    matrixCol = count(firstPart.begin(), firstPart.end(), ',') + 1;
                }
                //if are steal reading the matrix line
                //we check iy bu counting by the number comma of in line
                if (count(firstPart.begin(), firstPart.end(), ',') + 1 == matrixCol) {
                    //we will insert every line of the matrix to the vector
                    matrixStringVector.push_back(firstPart);
                    matrixRow += 1;
                } else {
                    //we got noe the start position and end position
                    //split the values by ","
                    stringstream ss(firstPart);
                    string valStr;
                    vector<int> values;
                    int k = 0;
                    while (getline(ss, valStr, ',')) {
                        int val = stoi(valStr);
                        values.push_back(val);
                        k++;
                    }
                    if (index == 0) {
                        //we are in the line of the start position
                        startLocation = pair<int, int>(values.at(0), values.at(1));
                        index += 1;
                    } else {
                        //we are in the line of the end position
                        goalLocation = pair<int, int>(values.at(0), values.at(1));
                    }
                }
            }
            //in the next iteration we will handle the secondPart after the \n
            firstBuffer = secondPart;
        }

//        string solution = "sol";
//        const char *solutionChar = solution.c_str();
//        send(client_socket, solutionChar, solution.size(), 0);
//        return;

        //after we read all the data from the file
        //creating the matrixProblem
        MatrixProblem *matrix = new MatrixProblem(matrixStringVector, startLocation, goalLocation, matrixRow,
                                                  matrixCol);
        //create string that represent the problem with hash function
        string matrixStringHash = matrix->toString();

        //OA - MatrixSolverBestFS
        this->solver = new MatrixSolverBestFS();
        string name = this->solver->getSolverName();
        string problemName = matrixStringHash.append(name);
        //if we already solve this problem
        if (this->cacheManager->find(problemName)) {
            string solution1 = this->cacheManager->get(problemName);
            const char *solutionChar1 = solution1.c_str();
            send(client_socket, solutionChar1, solution1.size(), 0);

        } else {
            //if we need to solve the problem now
            //we will sent to solver the problem as matrix
            string solution = this->solver->solve(*matrix);
            //we will save the problem as matrix string and the solution as matrix string
            this->cacheManager->save(problemName, solution);
            const char *solutionChar = solution.c_str();
            send(client_socket, solutionChar, solution.size(), 0);
        }
    }
};




#endif //PART2_MYCLIENTHANDLER_H
