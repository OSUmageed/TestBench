#include <fstream>
#include <ostream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../json.hpp"
#include <mpi.h>
#include <omp.h>
#include <math.h>

#include <string>
//Random?

#define LIM     2e6
#define DEPTH   5

static int ranks, sz, sth;
size_t dsz;

using namespace std;
using jsons = nlohmann::json;

jsons jtime;

double stFun(double *ar, int idx, int i)
{
    if (i == 1) return ar[idx];
    double rslt = 0.0;
    for (int k = -sth; k<=sth; k++)
    {
        rslt += ar[k]; 
    }
    ar[idx] *= rslt; 
    return stFun(ar, idx, i-1);
}

void ompTest()
{
    int stencil = 1; // Stencil will be 1,3,5,7,9 and loop next line
    //for
    sth = stencil/2;
    int k = 1024;
    double *marray;
    double ti, tf;
    while (k<LIM)
    {
        k *= 2;
        malloc((void **) &marray, k*dsz);
        // Make random numbers
        for (int b=0; b<DEPTH; b++)
        {
            ti = omp_get_wtime();
            #pragma omp parallel for
            for (int n=0; n<k; n++)
            {
                marray[n] = stFun(marray, n, b+1);
            }
            tf = ti - omp_get_wtime();
            jtime["OMP"][to_string(k)][to_string(b)] = tf;
        }
        free(marray);
    }
}

// Test MPI vs OMP parallel performance.
int main(int argc, char *argv[])
{
    dsz = sizeof(double);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ranks);
    MPI_Comm_size(MPI_COMM_WORLD, &sz);

    bool typ = (sz == 1);

    if (typ)
    {
        ompTest();
    }

    ofstream timi;
    timi.open(argv[2], ios::app);
    timi << jtime;
    return 0;
}


