
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <algorithm>
#include <string>
#include <cuda.h>
#include <cuda_runtime.h>
#include <mpi.h>
#include <omp.h>
#include <nvml.h> // If I use this I'll need to start a context first.


// "MV2_COMM_WORLD_LOCAL_RANK"
// #define ENV_LOCAL_RANK		"OMPI_COMM_WORLD_LOCAL_RANK"

int rank, nthreads, nGpu, rlen=40;
cudaDeviceProp *props;

using namespace std;

void getDeviceInformation();
{
    cudaGetDeviceCount(nGpu);
    nthreads = omp_get_num_procs();
    MPI_Get_processor_name(&procN,  &rlen);

    if (nGpu)
    {
        for (int k=0; k<nGpu; k++)
        {
            cudaGetDeviceProp(&props, k);
            cout << rank << " " << procN << " " << nthreads << " " << nGpu;
            cout << " " << k << " " props.name << " " << props.multiprocessorcount;
            cout << " " << props.major << "." << props.minor << endl;
        }
    }
    else
    {
        cout << rank << " " << procN << " " << nthreads << " " << nGpu << endl;
    }

    //Maybe just set cuda compute mode = 1 (exclusive)

     

    // From this I want what GPUs each proc can see, and how many threads they can make
    // This may require nvml to get the UUID of the GPUS, pass them all up to the 
    // Master proc to decide which proc gets which gpu.
}

// Test device sight.
int main(int argc, char *argv[])
{

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (!rank) cout << "rank -- cpuname -- nThreads -- nGpu -- GPU# -- GPUname -- #SM -- CC" << endl;
    getDeviceInformation();
    MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
}
