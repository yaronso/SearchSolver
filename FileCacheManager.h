//
// Created by yaron on 08/01/2020.
//

#ifndef PART2_FILECACHEMANAGER_H
#define PART2_FILECACHEMANAGER_H

#include "CacheManager.h"
#include "unordered_map"
#include <fstream>
#include "FileCacheManager.h"
#include "map"
#include "unordered_map"
#include <iostream>


template<typename S>
//the problem always will be represented by string
class FileCacheManager : public CacheManager<S> {
//private:
    //map <string, string> problemMap;
    //int index = 0;
private:
    list<pair<string, S>> list1;
    unordered_map<string, typename list<pair<string, S>>::iterator> cacheMap;
    map <string, string> solvedProblem; //from problem to string ;
    unsigned int capacity = 5; // maximum capacity of cache
public:
    bool find(string problem) override {
        return solvedProblem.find(problem) != solvedProblem.end();
    }

    S get(string problem) override {
        //if not in cache
        string sol = "error";
        if (cacheMap.find(problem) == cacheMap.end()) {
            fstream myFile;
            string fileName = problem.append(".txt");
            string file_name = problem;
            myFile.open(file_name, ios::in);
            if (!myFile.is_open()) {
                cout << "an error - file not found";
            } else {
                string solution = "";
                string line;
                while (getline(myFile, line)) {
                    solution.append(line);
                }
                myFile.close();
                //we need to insert to the cache list
                insertNewObjToList(problem, solution);
                return solution;
            }
        } else {
            //if its in cache list
            S solution = ((*cacheMap[problem]).second);
            //update the cache list
            insertExistObjToList(problem, solution);
            return solution;
        }
        return sol;
    }

    //our problem is hashed string
    void save(string problem, string solution) override {
        //CACHE
        //we need to insert the obj to cache
        insertNewObjToList(problem, solution);

        //DISK
        //string fileName = problem;
        fstream io_file;
        string fileName = problem.append(".txt");
        io_file.open(fileName, ios::out);
        if (!io_file.is_open()) {
            cout << "error in opening the file" << endl;
        }
        //now insert to the file
        io_file << solution;

        io_file.close();
        //adding the file to the problemMap
        this->solvedProblem[problem] = fileName;
    }

    void insertExistObjToList(string problem, S &solution) {
        //change the location of the object
        list1.erase(cacheMap[problem]);
        // update reference
        pair<string, S> pair1(problem, solution);
        list1.push_front(pair1);
        cacheMap[problem] = list1.begin();
    }

    void insertNewObjToList(string &problem, S &solution) {
        //if cache is full
        if (list1.size() == capacity) {
            string last = list1.back().first;
            list1.pop_back();
            cacheMap.erase(last);
        }
        pair<string, S> pair1(problem, solution);
        list1.push_front(pair1);
        cacheMap[problem] = list1.begin();
    }
};


#endif //PART2_FILECACHEMANAGER_H