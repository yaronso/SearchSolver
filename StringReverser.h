//
// Created by yaron on 08/01/2020.
//

#ifndef PART2_STRINGREVERSER_H
#define PART2_STRINGREVERSER_H

#include "Solver.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class StringReverser : public Solver<string, string> {
public:
    // implements the virtual function of Solver abstract class - solve()
    string solve(string str) {
        string reverse;
        for (string::iterator it = str.end()-1; it != str.begin(); it--) {
            if (*it == '\\') {
                break;
            }
            reverse.append(1,*it);
        }
        cout << "Problem was solved by the string reverser"<<endl;
        return reverse;
    }

    Solver* clone() {
        return this;
    }
};

#endif //PART2_STRINGREVERSER_H
