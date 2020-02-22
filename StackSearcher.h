//
// Created by yaron on 11/01/2020.
//

#ifndef PART2_STACKSEARCHER_H
#define PART2_STACKSEARCHER_H

#include "Isearcher.h"
#include "stack"

/*
 * This class extends the ISearcher interface, and represents an abstract class of an algorithm
 * which solve a search problem using a stack
 */
template< typename S,typename T>
class StackSearcher : public ISearcher<S, T> {
protected:
    list<State<T> *> visitedList;
    stack<State<T> *> stateStack; // This stack holds the states/nodes which are waiting to be processed
    int evaluatedNodes; // number of nodes evaluated by the algorithm
    int pathLength; // represents the length of the min path which was found by the algorithm

    /* When we will want to insert a theState to the open list we will push it to the front of the
    * list to represents pushing an object to a stack
    */
    void addToVisitedList(State<T> *s) {
        this->visitedList.push_front(s);
    }

    /* When we will want to extract a theState from the open list we will return it and erase him from the list
    * to represents popping an object from a stack
    */
    State<T> *topAndPopStack() {
        State<T> *state = this->stateStack.top();
        this->stateStack.pop();
        return state;
    }

public:
    // constructor
    StackSearcher() {
        evaluatedNodes = 0;
    }

    // will be implement by a specific algorithm (like BFS)
    virtual S search(ISearchable<T> *searchable)  = 0;


    // get how many nodes were evaluated by the algorithm
    int getNumberOfNodesEvaluated() {
        return evaluatedNodes;
    }

    // This method returns what is the the minimum path we found using the algorithm
    virtual int getPathLength() {
        return pathLength;
    }

};

#endif //PART2_STACKSEARCHER_H
