#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <sched.h>
#include <unistd.h>

static int ranks, rlen=800;

// mpirun -np 2 ../mpiBased/bin/mpi_omp 32

using namespace std;

void getDeviceInformation()
{
    char procN[rlen];
    int nthreads = omp_get_num_procs();
    MPI_Get_processor_name(procN,  &rlen);
    int cid = sched_getcpu();

    cout << ranks << " " << procN << " " << nthreads << endl;
}

void threadLocTest(int nt)
{
    #pragma omp parallel for num_threads(nt)
    for (int n=0; n<nt; n++)
    {
        double tm = omp_get_wtime();
        int tid = omp_get_thread_num();
        int cid = sched_getcpu();
        printf("Rank: %i --- Thread: %i --- on CPU: %i --- Time %.9f.\n", ranks, tid, cid, tm);
        sleep(5);
        fflush(stdout); 
    }
}

// Test device sight.
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ranks);
    if (!ranks) cout << "rank -- cpuname -- nThreads" << endl;
    MPI_Barrier(MPI_COMM_WORLD);
    getDeviceInformation();
    MPI_Barrier(MPI_COMM_WORLD);
    cout << endl;

    if (!ranks) cout << "rank -- tid -- cpuid -- Time" << endl;
    // Look at where the threads are place in OMP when running with two+ procs
    int nt = atoi(argv[1]); //Nthreads
    threadLocTest(nt);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}