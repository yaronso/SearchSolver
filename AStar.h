//
// Created by yaron on 13/01/2020.
//

#ifndef PART2_ASTAR_H
#define PART2_ASTAR_H

#include "PrioritySearcher.h"


// This class implements the PrioritySearcher abstract class as a A* algorithm
template<class S, class T>
class AStar : public PrioritySearcher<S, T> {
    string algoName = "AStar";

public:
    string getName() override {
        return this->algoName;
    }

    // This method gets a searchable problem runs the A* algorithm and returns the minimal path it found
    S search(ISearchable<T> *searchable) {
        // getting the source vertex
        State<T> *initState = searchable->getInitialState();
        // we set the vertex s: s.f = s.g + s.h to zero
        initState->setCost(0);
        //initState->setSumOfCosts()(initState->getSumOfCosts() + getManDist(initState, searchable->getGoalState()));
        // we enqueue the first vertex s to the open astar queue
        PrioritySearcher<S, T>::addToOpenList(initState);
        // creates the closed astar queue
        multiset<State<T> *, CompareCost<T>> closed;
        // while the open queue isn't empty
        while (PrioritySearcher<S, T>::openList.size() > 0) {
            // inherited from PrioritySearcher, removes the least theState n
            State<T> *n = PrioritySearcher<S, T>::popOpenList();
            closed.insert(n); // We insert it into the close list so it won't be processed again
            // If we have reached the goal theState we will trace back the path we have found and return it
            if (searchable->isGoalState(n)) {
                // We decrease the last heuristic from the goal theState: n
                //n->setSumOfCosts(n->getSumOfCosts() - getManDist(n, searchable->getGoalState()));
                // back traces through the parents
                return ISearcher<S, T>::backTrace(n, searchable);
                // return the total number if nodes that the algorithm passed (int)
                //return this->evaluatedNodes;
            }
            // calling the delegated method, returns a list of states with n as a parent
            list<State<T> *> successors = searchable->getAllPossibleStates(n);
            // We iterate through all the successors theState
            for (auto it = successors.begin(); it != successors.end(); it++) {
                State<T> *neighbor = *it;
                double possibleTrail = n->getSumOfCosts() + neighbor->getCost();
                // if the theState isn't found in the open list and also the not in the closed list
                if ((!isInSet(PrioritySearcher<S, T>::openList, neighbor)) && (!(isInSet(closed, neighbor)))) {
                    notInOpenClose(neighbor, n, possibleTrail, searchable);
                    continue;
                }
                    // in a case we can improve our path
                else if (possibleTrail < neighbor->getSumOfCosts()) {
                    improvePath(neighbor, n, possibleTrail, searchable);
                    continue;
                }
            }
        }
        cout << "cant find path"<<endl;
        return "cant find path";
    }

    void improvePath(State<T> *neighbor, State<T> *currentState, double possibleTrail, ISearchable<T> *searchable) {
        State<T> *goalState = searchable->getGoalState();
        neighbor->setCameFrom(currentState);
        neighbor->setSumOfCosts(possibleTrail);
        setHeuristic(neighbor, goalState, searchable);
        PrioritySearcher<S, T>::openList = updatePriorityQueue(PrioritySearcher<S, T>::openList);
    }

    void enterToOpen(State<T> *pState) {
        State<pair<int, int>> *pst = pState;
        this->addToOpenList(pst);
    }

    void notInOpenClose(State<T> *neighbor, State<T> *currentState, double possibleTrail,
                        ISearchable<T> *searchable) {
        State<pair<int, int>> *neighbor1 = neighbor;
        State<pair<int, int>> *currentState1 = currentState;
        State<T> *goalState = searchable->getGoalState();
        neighbor1->setCameFrom(currentState1);
        neighbor1->setSumOfCosts(possibleTrail);
        setHeuristic(neighbor, goalState, searchable);
        enterToOpen(neighbor1);
    }

    void setHeuristic(State<T> *neighbor, State<T> *goal, ISearchable<T> *searchable) {
        State<pair<int, int>> *ne = neighbor;
        State<pair<int, int>> *go = goal;
        State<pair<int, int>> *direction = searchable->getLocationInSearchable(ne->getState().first,
                                                                               ne->getState().second);
        int xNE = direction->getState().first;
        int yNE = direction->getState().second;
        direction = searchable->getLocationInSearchable(go->getState().first, go->getState().second);
        int xGO = direction->getState().first;
        int yGO = direction->getState().second;
        // call setHeu in theState class to set the heuristic distance of the neighbor theState
        neighbor->setHeu(abs(xGO - xNE) + abs(yGO - yNE));
    }

    // THE HEURISTIC METHOD - This method calculates the Manhattan distance of a theState from the goal theState and returns it
    int getManDist(State<pair<int, int>> *currState, State<pair<int, int>> *goalState) {
        int x = goalState->getState().first - currState->getState().first;
        int y = goalState->getState().second - currState->getState().second;
        return abs(x) + abs(y);
    }


    multiset<State<T> *, CompareCost<T>> updatePriorityQueue(multiset<State<T> *, CompareCost<T>> enteredQueue) {
        multiset<State<T> *, CompareCost<T>> newQueue;
        while (enteredQueue.size() > 0) {
            auto it = enteredQueue.end();
            State<T> *sa = *it;
            newQueue.insert(sa); // newqueue.push(entered.top());
            enteredQueue.erase(sa); // entered.pop();
        }
        return newQueue;
    }

    // This method checks if a theState is found in the open list, and if it's stateCost is smaller then the theState inside
    // the open list we will replace it's stateCost with the new stateCost
    virtual void saveMin(State<T> *currState, State<T> *n) {
        for (auto it = PrioritySearcher<S, T>::openList.begin(); it != PrioritySearcher<S, T>::openList.end(); it++) {
            State<T> *s = *it;
            // means it is in the open list
            if (s->Equals(currState)) {
                // check the costs - if the condition is true
                if (currState->getSumOfCosts() + s->getCost() < s->getSumOfCosts()) {
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

    // This method checks if a theState is inside a multiset
    bool isInSet(multiset<State<T> *, CompareCost<T>> setOfState, State<T> *currState) {
        for (auto it = setOfState.begin(); it != setOfState.end(); it++) {
            State<T> *s = *it;
            if (s->Equals(currState))
                return true;
        }
        return false;
    }

};

#endif //PART2_ASTAR_H
