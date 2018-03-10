#ifndef KERNELMAIN_H
#define KERNELMAIN_H

//#include "equation.h"
#include "equation.h"

class Solver
{
private:
    Equation *eq;
    FILE *timeOut;
    int tstep, bitAlloc;
    size_t smem;
    states *hState, *dState;
    str kernelType, schemeType;
    double t_eq, twrite, timed;

    void storeSolution();
    void classic();
    void swept();

public:
    //Some members
    Solver(Equation *eqparam, std::string scheme, std::string kernel);
    
    ~Solver();

    void solveEquation();

    void writeFiles();

};

#endif