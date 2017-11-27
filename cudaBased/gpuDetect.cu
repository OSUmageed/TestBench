
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
// #include <typeinfo>
#include <cuda.h>
#include <cuda_runtime.h>
#include <mpi.h>
//#include <nvml.h> // If I use this I'll need to start a context first.

// "MV2_COMM_WORLD_LOCAL_RANKs"
// #define ENV_LOCAL_RANKs		"OMPI_COMM_WORLD_LOCAL_RANKs"

int ranks, nthreads, nGpu, rlen=800;
cudaDeviceProp props;


using namespace std;

void getDeviceInformation()
{
    char procN[rlen];
    cudaGetDeviceCount(&nGpu);
    MPI_Get_processor_name(procN,  &rlen);

    cout << "---------- " << procN << " --------" << endl;

    if (nGpu)
    {
        for (int k=0; k<nGpu; k++)
        {
            cudaGetDeviceProperties(&props, k);
            cout << ranks << " " << procN << " " << nthreads << " " << nGpu;
            cout << " " << k << " "<< props.name << " " << props.multiProcessorCount;
            cout << " " << props.major << "." << props.minor << endl;
        }
    }
    else
    {
        cout << ranks << " " << procN << " " << nthreads << " " << nGpu << endl;
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
    MPI_Comm_rank(MPI_COMM_WORLD, &ranks);
    if (!ranks) cout << "ranks -- cpuname -- nThreads -- nGpu -- GPU# -- GPUname -- #SM -- CC" << endl;
    getDeviceInformation();
    MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
}
