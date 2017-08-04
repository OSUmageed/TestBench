#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <mpi.h>
#include <omp.h>


int rank, nthreads, rlen=800;
char *procN;

using namespace std;

void getDeviceInformation()
{
    nthreads = omp_get_num_procs();
    MPI_Get_processor_name(&procN,  &rlen);

    cout << rank << " " << procN << " " << nthreads << endl;

    // From this I want what GPUs each proc can see, and how many threads they can make
    // This may require nvml to get the UUID of the GPUS, pass them all up to the 
    // Master proc to decide which proc gets which gpu.
}

// Test device sight.
int main(int argc, char *argv[])
{

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (!rank) cout << "rank -- cpuname -- nThreads" << endl;
    getDeviceInformation();
    MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
}