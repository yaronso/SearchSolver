//
// Created by yaron on 10/01/2020.
//

#ifndef PART2_STATE_H
#define PART2_STATE_H
#include <string>
using namespace std;

template <typename T>
class State {
    T theState;
    int stateCost; // stateCost to reach this theState (set by a setter)
    int sumOfCosts; // sum of costs for the BEST first search algorithm
    State<T>* cameFrom; // the theState we came from to this theState (setter)
    string cameFromDir; // the direction it came from
    int heuristic;


public:
    // constructor
    State<T>(T state1, int cost1)
    {
        this->theState = state1;
        this->stateCost = cost1;
        this->sumOfCosts = cost1;
    }


    void setCameFromDirection(string dir){
        this->cameFromDir = dir;
    }

    // we override Object's Equals method
    bool Equals(State<T>* other)
    {
        if (this->theState == other->theState)
            return true;
        else
            return false;
    }

    int getCost()
    {
        return this->stateCost;
    }

    void setCost(int cost)
    {
        this->stateCost = cost;
    }

    int getSumOfCosts() {
        return this->sumOfCosts;
    }

    void setSumOfCosts(int sumOfCosts1) {
        this->sumOfCosts = sumOfCosts1;
    }

    void setHeu(int num) {
        this->heuristic = num;
    }

    void setCameFrom(State<T>* state)
    {
        this->cameFrom = state;
    }

    void deleteCameFrom(State<T>* state){
        this->cameFrom = NULL;
    }

    State<T>* getCameFrom()
    {
        return cameFrom;
    }

    T getState()
    {
        return this->theState;
    }

    string getCameFromDir()
    {
        return this->cameFromDir;
    }

};
#endif //PART2_STATE_H
