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
// #include <cuda.h>
// #include <cuda_runtime.h>
#include <mpi.h>
// #include <omp.h>
#include "json.hpp"

// using jsons = nlohmann::json;

// "MV2_COMM_WORLD_LOCAL_RANK"
// #define ENV_LOCAL_RANK		"OMPI_COMM_WORLD_LOCAL_RANK"

// void SetDeviceBeforeInit()
// {
// 	char * localRankStr = NULL;
// 	int rank = 0, devCount = 0;

// 	// We extract the local rank initialization using an environment variable
// 	if ((localRankStr = getenv(ENV_LOCAL_RANK)) != NULL)
// 	{
// 		rank = atoi(localRankStr);		
// 	}

// 	cudaGetDeviceCount(&devCount);
//     int mdev = rank % devCount;
// 	cudaSetDevice(mdev);
//     std::cout << "Before Init: Process " << rank << " has device " << mdev << std::endl;
//     // On the CPU side
//     int nthreads = omp_get_num_procs();
//     std::cout << "Rank:  " << rank << " has CPU threads visible " << nthreads << std::endl;
// }

// // Test device sight.
// int main(int argc, char *argv[])
// {
//     int rank, mydev;
//     for (int k=0; k<argc; k++) cout << argv[k] << " " << endl;

//     SetDeviceBeforeInit();
//     MPI_Init(&argc, &argv);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     cudaGetDevice(&mydev);
//     cout << "After Init: Process " << rank << " has device " << mydev << endl;
//     MPI_Barrier(MPI_COMM_WORLD);
// 	MPI_Finalize();
// }

// // Test json
// int main(int argc, char *argv[])
// {
//     std::ifstream imzep("test.json", std::ifstream::in);
//     jsons myJ;
//     imzep >> myJ;
//     std::cout << myJ.dump(4) << std::endl;

//     int dt = myJ["dt"]; 
//     std::cout << typeid(myJ["dm"]).name() << std::endl;
//     imzep.close();

//     std::cout << dt*5 << std::endl;
//     return 0;
// }

using namespace std;

#include <unistd.h>

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

