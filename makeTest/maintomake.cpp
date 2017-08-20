#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

using namespace std;

static int ranks, siz;

void testParallel()
{
    //Some Code here to make all the threads to.  See whether MPI or OMP are faster.
}

// Test device sight.
int main(int argc, char *argv[])
{
    int nt;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ranks);
    MPI_Comm_size(MPI_COMM_WORLD, &siz);
    if (size == 1) 
    {
        nt = omp_get_num_procs();
    }
    else
    {
        nt = 1;
    }

    cout << nt << endl;

    return 0;
}