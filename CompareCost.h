//
// Created by yaron on 11/01/2020.
//

#ifndef PART2_COMPARECOST_H
#define PART2_COMPARECOST_H
#include "State.h"

// in the following class we use object function that checks the sum of costs
// per each theState and compare them
template <class T>
struct CompareCost {
public:
    bool operator()( State<T>* s1, State<T>* s2) const {
        return  (s1->getSumOfCosts() < s2->getSumOfCosts());
    }
};
#endif //PART2_COMPARECOST_H
