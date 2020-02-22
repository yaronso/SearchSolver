//
// Created by adi on 08/01/2020.
//

#ifndef PART2_SOLVER_H
#define PART2_SOLVER_H


#include "string.h"
using namespace std;
// will receive a generic problem and solution
template <typename P, typename S>
class Solver{
    //P problem;
    //S solution;
public:
   // virtual string solve(string problem) = 0;
    virtual S solve(P) = 0;
   virtual Solver* getClone() = 0;
   virtual ~Solver() = default;
    virtual string getSolverName ()=0;
    };

#endif //PART2_SOLVER_H
