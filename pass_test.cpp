/*
    Just a testing main program for the functions
*/

// Compile IT:  nvcc -o sandbx sandbox.cu -lm -restrict -gencode arch=compute_35,code=sm_35

//nvcc -o sandbx sandbox.cu ../equations/Euler/Euler_Device.cu -lm -gencode arch=compute_35,code=sm_35 
// g++ -o sndbx sandbox.cpp -O3 -lm --std=c++11
// Yeah it works with g++ though (5.4)
// You also need a dummy variable when you use the value.

// mpic++ -o sndbx sandbox.cpp -O3 -lm --std=c++11 -march=native -lcudart OK

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <mpi.h>
#include <unistd.h>
#include "json.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    int ranks;
    int nprocs;
    int a;
    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &ranks);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int *bd, bsize = 2000;
    MPI_Status status;
    MPI_Request req; 
    MPI_Send_init(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &req) ;
    // MPI_Buffer_attach(malloc(bsize), bsize);
    int stp = 21;

    if (!ranks)
    {
        sleep(1);
        for (int k=1; k<stp; k++)
        {
            a = k;
            MPI_Start(&req);
            cout << ranks << " " << a << endl;
        }
    }
    else
    {
        int c;
        // sleep(ranks*1);
        
        for (int b=3; b<stp+2; b++)
        {
            MPI_Recv(&c, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            cout << ranks << " " << c << endl;
        }
       
    }
    // MPI_Wait(&req, &status);
    // // MPI_Buffer_detach(&bd, &bsize);
    // MPI_Barrier(MPI_COMM_WORLD);
    // MPI_Request_free(&req);
    MPI_Finalize();
    return 0;
}

