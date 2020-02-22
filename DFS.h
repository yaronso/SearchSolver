//
// Created by adi on 11/01/2020.
//

#ifndef PART2_DFS_H
#define PART2_DFS_H

#include "ISearchable.h"
#include "StackSearcher.h"
#include <deque>
#include "cmath"
#include "list"

using namespace std;

template<class S, class T>
class DFS : public StackSearcher<S, T> {
private:
    list<State<T> *> adjList;
    string algoName = "DFS";

public:
    string getName() override {
        return this->algoName;
    }
    S search(ISearchable<T> *searchable) {
        //getting the first vertex to start from
        State<T> *startState = searchable->getInitialState();
        //we will run DFS by using a stack,path start theState and searchable (our matrix or graph)
        //       int totalNumOfNodes = runDFS(startState, searchable);
        //string solution = to_string(totalNumOfNodes);
//        string solution= this->backTrace(searchable->getGoalState());
        //       return solution;
        return runDFS(startState, searchable);
    }

    S runDFS(State<T> *startState, ISearchable<T> *searchable) {
        // we set the adjacent list of the source vertex
        adjList = searchable->getAllPossibleStates(startState);

        // Mark the current node as visited and enqueue it
        this->addToVisitedList(startState);
        // add the source node to the open list which is a stack data structure
        this->stateStack.push(startState);
        this->evaluatedNodes++;
        // create an iterator to iterate through the adjacency list
        typename std::list<State<T> *>::iterator i;
        // while the stack is not empty
        while (!this->stateStack.empty()) {
            // Pop a vertex from stack;
            State<T> *u = this->topAndPopStack();
            // if the popped theState was not visited marked it
            if (!isInVisitedList(u)) {
                // increase the number of visited nodes
                this->evaluatedNodes++;
                //the came from theState is the last theState in the visited List
                State<T> *prevState = this->visitedList.front();
                this->addToVisitedList(u);
                u->setCameFrom(prevState);
                //set the new sum of stateCost
                int newCost = prevState->getSumOfCosts() + u->getCost();
                u->setSumOfCosts(newCost);
                //if we in the goal theState
                if (searchable->isGoalState(u)) {
                    return ISearcher<S, T>::backTrace(u, searchable);
                    //if we want to return the total number if nodes that the algorithm passed
                    //return to_string(this->evaluatedNodes);
                }

            }
            // Get all adjacent vertices of the popped vertex u
            // If a adjacent has not been visited, then push it
            // to the stack.
            list<State<T> *> uAdjList = searchable->getAllPossibleStates(u);
            typename std::list<State<T> *>::iterator UIterator;
            for (UIterator = uAdjList.begin(); UIterator != uAdjList.end(); ++UIterator) {
                if (!isInVisitedList(*UIterator)) {
                    this->stateStack.push(*UIterator);
                }
            }
        }
        cout <<"cant find path" <<endl;
        return "cant find path";
    }

    bool isInVisitedList(State<T> *state) {
        typename std::list<State<T> *>::iterator k;
        bool isInList = false;
        for (k = this->visitedList.begin(); k != this->visitedList.end(); ++k) {
            if (state == *k) {
                isInList = true;
            }
        }
        return isInList;
    }
};

#endif //PART2_DFS_H