//
// Created by yaron on 11/01/2020.
//

#ifndef PART2_PRIORITYSEARCHER_H
#define PART2_PRIORITYSEARCHER_H

#include <queue>
#include <sstream>
#include "Isearcher.h"
#include "State.h"
#include "CompareCost.h"


using namespace std;

template<class S, class T>
class PrioritySearcher : public ISearcher<S, T> {
protected:
    /* This multiset holds the states which are waiting to be processed, it is sorted from the smallest stateCost
    * to the largest stateCost to represent an priority queue
    */
    multiset<State<T> *, CompareCost<T>> openList;
    int evaluatedNodes;
    int pathLength;

    /* When we insert a theState to the open list we will insert it into the open list
     * and the multiset will sort itself by the CompareCost object function.
     */
    void addToOpenList(State<T> *s) {
        this->openList.insert(s);
    }


    /* When we will want to extract a theState from the open list we will erase it from the open list,
     * return it, and the multiset will sort itself accordingly.
     */
    State<T> *popOpenList() {
        evaluatedNodes++;
        auto it = openList.begin();
        State<T> *sa = *it;
        openList.erase(it);
        return sa;
    }


public:


    PrioritySearcher() {
        evaluatedNodes = 0;
    }

    // will be implemented in the Best First Search
    virtual S search(ISearchable<T> *searchable) = 0; // the search method
    // get how many nodes were evaluated by the algorithm
    int getNumberOfNodesEvaluated() {
        return evaluatedNodes;
    }

    // This method returns what is the the min path we found using the algorithm
    virtual int getPathLength() {
        return pathLength;
    }

};

#endif //PART2_PRIORITYSEARCHER_H
