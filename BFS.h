//
// Created by yaron on 12/01/2020.
//

#ifndef PART2_BFS_H
#define PART2_BFS_H

#include "QueueSearcher.h"

template<class S, class T>
class BFS : public QueueSearcher<S, T> {
private:
    // the adjancet list of the source vertex
    list<State<T> *> adjList;
    string algoName = "BFS";

public:
    string getName() override {
        return this->algoName;
    }
    S search(ISearchable<T> *searchable) {
        // getting the source vertex
        State<T> *startState = searchable->getInitialState();
        // run the main function of the BFS
        //S totalNumOfNodes = runBFS(startState, searchable);
        return runBFS(startState, searchable);
        //string solution = to_string(totalNumOfNodes);
        //return solution;

    }

    S runBFS(State<T> *startState, ISearchable<T> *searchable) {
        // we set the adjacent list of the source vertex
        adjList = searchable->getAllPossibleStates(startState);
        // Mark the current node as visited and enqueue it
        this->visitedList.push_front(startState);
        // Q <- enqueue(s)
        this->addToQueue(startState);
        // 'i' will be used to get all adjacent vertices of a vertex
        typename std::list<State<T> *>::iterator i;
        // while the queue is not empty
        while (!this->stateQueue.empty()) {
            // Dequeue a vertex from queue
            State<T> *u = this->topAndPopFromQueue();

            // Get all adjacent vertices of the dequeue
            // vertex u. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            list<State<T> *> adjU = searchable->getAllPossibleStates(u);
            typename std::list<State<T> *>::iterator UIterator;
            for (UIterator = adjU.begin(); UIterator != adjU.end(); UIterator++) {
                // if the adjacent was not visited
                if (!isInVisitedList(*UIterator)) {
                    // set where it came from
                    State<T> *neighbor = *UIterator;
                    neighbor->setCameFrom(u);
                    //set the sum of stateCost
                    neighbor->setSumOfCosts(u->getSumOfCosts()+neighbor->getCost());
                    if (searchable->isGoalState(*UIterator)){
                        this->evaluatedNodes++;
                        //return to_string(this->evaluatedNodes);
                        return  ISearcher<S, T>::backTrace(*UIterator, searchable);
                    }
                    // mark it as visited
                    this->visitedList.push_front(*UIterator);
                    this->stateQueue.push(*UIterator);
                    // increase the number of visited nodes
                    this->evaluatedNodes++;
                }
            }

        }
        // return the total number if nodes that the algorithm passed
        //return to_string(this->evaluatedNodes);
        cout << "cant find path" <<endl;
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

#endif //PART2_BFS_H
