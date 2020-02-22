//
// Created by yaron on 11/01/2020.
//

#ifndef PART2_ISEARCHER_H
#define PART2_ISEARCHER_H
#include "ISearchable.h"
#include <vector>
#include <deque>

// The following interface represent the algorithm itself which takes part of the bridge design pattern.
  // we use the dependency injection so we can solve any kind of search problem by different search algorithms.
template <typename S,class T>
class ISearcher {
private:
    int pathLength;
    int evaluatedNodes;


public:
    virtual string getName() =0;
    virtual ~ISearcher() = default;
    virtual S search (ISearchable<T>* searchable) = 0; // the search method - dependency injection
    virtual int getNumberOfNodesEvaluated() = 0; // get how many nodes were evaluated by the algorithm
    virtual int getPathLength() = 0; // get how many nodes were evaluated by the algorithm
    // This method traces back the path the algorithm found, and returns which steps were taken on this path
    string backTrace(State<T> *s, ISearchable<T> *searchable) {
        deque<string> path;
        string ans = "";
        //int numberOfStates =0;
        // pathLength holds to stateCost to reach to that theState
        this->pathLength = s->getCost();
        State<T> *initState = searchable->getInitialState();
        // while the theState isn't the source theState
        while (!(s->Equals(initState))) {
            // put in the deque the direction that the theState was came from
            //numberOfStates+=1;
            State<pair<int,int>>* currentState = s;
            State<pair<int,int>>* prevState = s->getCameFrom();
            string stringg = searchable->getDirection(prevState,currentState);
            stringg.append("(");
            stringg.append(to_string(currentState->getSumOfCosts()));
            stringg.append(")");
            path.push_front(stringg);
            // increment the loop by the following command
            s = s->getCameFrom();
        }

        // use an iterator to save the path of the theState s
        auto it = path.begin();
        ans += *it;
        it++;

        for (; it < path.end(); it++) {
            ans += ",";
            ans += *it;
        }
        // return the pass of all the states
        return ans;
    }
};

#endif //PART2_ISEARCHER_H
