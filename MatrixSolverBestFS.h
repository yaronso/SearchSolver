//
// Created by adi on 13/01/2020.
//

#ifndef PART2_MATRIXSOLVERBESTFS_H
#define PART2_MATRIXSOLVERBESTFS_H

#include "Solver.h"
#include "ISearchable.h"
#include "Isearcher.h"
#include "BestFirstSearch.h"
#include "AStar.h"
#include "DFS.h"
#include "BFS.h"

//we receive specific problem type and solution type for our solver
class MatrixSolverBestFS : public Solver<MatrixProblem, string> {
private:
    //we have specific searcher - BestFirstSearch
    //ISearcher<string, pair<int, int>> *searcher = new BFS<string, pair<int,int>>();
    //ISearcher<string, pair<int, int>> *searcher = new DFS<string, pair<int,int>>();
    //ISearcher<string, pair<int, int>> *searcher = new AStar<string, pair<int,int>>();
    ISearcher<string, pair<int, int>> *searcher = new BestFirstSearch<string, pair<int, int>>();

    // we have specific searchable - searchableMatrix
    //ISearchable<pair<int, int>>* searchableMatrix;
public :
    //we will solve the problem by using the function search of BestFirstSearch
    string solve(MatrixProblem problem) override {
        return this->searcher->search(&problem);
    }

    Solver *getClone() {
        return new MatrixSolverBestFS();
    }

    string getSolverName (){
    return this->searcher->getName();
}


};

#endif //PART2_MATRIXSOLVERBESTFS_H
