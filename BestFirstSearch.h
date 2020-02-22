//
// Created by yaron on 11/01/2020.
//

#ifndef PART2_BESTFIRSTSEARCH_H
#define PART2_BESTFIRSTSEARCH_H

#include "ISearchable.h"
#include "PrioritySearcher.h"
#include <unordered_set>
#include <deque>

using namespace std;

// The following class implements the PrioritySearcher abstract class
// as a Best First Search algorithm as we saw in the lecture
template<class S, class T>
class BestFirstSearch : public PrioritySearcher<S, T> {
    string algoName = "BestFs";

public:

    string getName() override {
        return this->algoName;
    }
    /*
     * This method gets a searchable problem runs the Best First Search algorithm and returns
     * the minimal path it found
     */
    S search(ISearchable<T> *searchable) {
        // inherited from PrioritySearcher
        PrioritySearcher<S, T>::addToOpenList(searchable->getInitialState());
        multiset<State<T> *, CompareCost<T>> closed;
        // while the multi-set OpenList is not empty
        while (PrioritySearcher<S, T>::openList.size() > 0) {
            // dequeue the top theState/node in the multi-set OpenList
            State<T> *n = PrioritySearcher<S, T>::popOpenList();
            closed.insert(n);
            // if the node n is the goal theState
            if (searchable->isGoalState(n)) {
                // we will do back trace and return the solution
                return ISearcher<S, T>::backTrace(n, searchable);
            }
            // o.w we create a list for all the successors of n
            list<State<T> *> successors = searchable->getAllPossibleStates(n);
            // we iterate over each successor of node n:
            for (auto it = successors.begin(); it != successors.end(); it++) {
                // if the theState isn't found in the open list and also the closed list we will add it to the open list
                if ((!isInSet(PrioritySearcher<S, T>::openList, *it)) && (!(isInSet(closed, *it)))) {
                    // we save the theState
                    State<T> *s = *it;
                    // update that we came to s from n
                    s->setCameFrom(n);
                    s->setSumOfCosts(n->getSumOfCosts() + s->getCost());
                    // and move it to the open list
                    this->addToOpenList(s);
                }
                    /* if the theState isn't found in the closed list but is found in the open list,
                    * we will check if it has smaller
                    * stateCost then what is already found in the open list and if it has we will replace the old stateCost with
                    * the new one

                else if (!(isInSet(closed, *it))) {
                    saveMin(*it, n);
                }*/
                    // check if there is a greater path
                else {
                    State<T> *s = *it;
                    double sTrailCost = s->getSumOfCosts();
                    double errowToState = s->getCost();
                    double newTrailCost = n->getSumOfCosts() + errowToState;
                    // check if there is a new path
                    if (newTrailCost < sTrailCost) {
                        // if it is not in the open list
                        if (!isInSet(PrioritySearcher<S, T>::openList, s)) {
                            this->addToOpenList(s);
                            // o.w - adjust it
                        } else {
                            s->setCameFrom(n);
                            s->setSumOfCosts(newTrailCost);
                            PrioritySearcher<S, T>::openList = updatePriorityQueue(PrioritySearcher<S, T>::openList);
                        }
                    }
                }
            }
        }
        return "did not find path";
    }

    multiset<State<T> *, CompareCost<T>> updatePriorityQueue(multiset<State<T> *, CompareCost<T>> enteredQueue) {
        multiset<State<T> *, CompareCost<T>> newQueue;// = new multiset<State<T> *, CompareCost<T>>();
        while(enteredQueue.size() > 0) {
            auto it = enteredQueue.end();
            State<T> *sa = *it;
            newQueue.insert(sa); // newqueue.push(entered.top());
            enteredQueue.erase(sa); // entered.pop();
        }
        return newQueue;
    }

    // The following method checks if a theState is found in the open list, and if it's stateCost is smaller then the theState inside
    // the open list we will replace it's stateCost with the new stateCost
    virtual void saveMin(State<T> *currState, State<T> *n) {
        for (auto it = PrioritySearcher<S, T>::openList.begin(); it != PrioritySearcher<S, T>
        ::openList.end(); it++) {
            // save the theState in s
            State<T> *s = *it;
            // means it is in the open list
            if (s->Equals(currState)) {
                // check the costs - if the condition is true
                if(currState->getSumOfCosts() + s->getCost() < s->getSumOfCosts())
                    // if (currState->getCost() <= s->getCost())
                    {
                    // set the father of the current theState
                    currState->setCameFrom(s->getCameFrom());
                    // adjust the open list
                    PrioritySearcher<S, T>::openList.erase(it);
                    this->addToOpenList(currState);
                }
                //return;
            }
        }
        // set the father of the current theState
        currState->setCameFrom(n);
        // if it's not in the open list add it to open list
        this->addToOpenList(currState);
        return;
    }

    // The following method checks if a theState is inside a multiset
    // we use it to check if any successor is inside the the open list or the closed list.
    bool isInSet(multiset<State<T> *, CompareCost<T>> setOfState, State<T> *currState) {
        for (auto it = setOfState.begin(); it != setOfState.end(); it++) {
            State<T> *s = *it;
            if (s->Equals(currState)) {
                return true;
            }
        }
        return false;
    }

    // get how many nodes were evaluated by the algorithm};
    int getNumberOfNodesEvaluated() override {
        return this->evaluatedNodes;
    }

    // get how many nodes were evaluated by the algorithm
    int getPathLength() override {
        return this->pathLength;
    }


};

#endif //PART2_BESTFIRSTSEARCH_H
