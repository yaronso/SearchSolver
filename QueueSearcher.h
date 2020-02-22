//
// Created by yaron on 11/01/2020.
//

#ifndef PART2_QUEUESEARCHER_H
#define PART2_QUEUESEARCHER_H

#include "Isearcher.h"
#include "CompareCost.h"
#include <deque>
#include <queue>

/*
 * This class extends the ISearcher interface, and represents an abstract class of an algorithm
 * which solve a search problem using a queue
 */
template<class S, class T>
class QueueSearcher : public ISearcher<S, T> {
protected:
    queue<State<T> *> stateQueue; // This dequeue holds the states/nodes which are waiting to be processed
    int evaluatedNodes; // number of nodes evaluated by the algorithm
    int pathLength; // represents the length of the min path which was found by the algorithm
    list<State<T> *> visitedList;

    /* When we will want to insert a theState to the open list we will push it to the back of the
     * list to represents pushing an object to a queue
    */
    void addToQueue(State<T> *s) {
        this->stateQueue.push(s);
    }

    /* When we will want to extract a theState from the open list we will return it and erase him from the list
     * to represents popping an object from a queue
     */
    State<T> *topAndPopFromQueue() {
        // get the theState/node from the open list
        State<T> *s = stateQueue.front();
        //State<T> *s = *(stateQueue.front());
        //pathLength += s->getCost();
        stateQueue.pop();
        return s;
    }

public:
    // constructor
    QueueSearcher() {
        evaluatedNodes = 0;
    }

    // will be implement by a specific algorithm (like BFS)
    virtual S search(ISearchable<T> *searchable) = 0;

    // get how many nodes were evaluated by the algorithm
    int getNumberOfNodesEvaluated() {
        return evaluatedNodes;
    }

    // This method returns what is the the minimum path we found using the algorithm
    virtual int getPathLength() {
        return pathLength;
    }

};

#endif //PART2_QUEUESEARCHER_H
