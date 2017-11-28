
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <utility>  
#include <cuda.h>
#include <cuda_runtime.h>
#include <mpi.h>
//#include <nvml.h> // If I use this I'll need to start a context first.

// "MV2_COMM_WORLD_LOCAL_RANKs"
// #define ENV_LOCAL_RANKs		"OMPI_COMM_WORLD_LOCAL_RANKs"
#define RLEN 800

int ranks, nprocs, nGpu;
cudaDeviceProp props;

using namespace std;

struct assigner {
    int bus, dom;
    char procN[RLEN];
    // void assigner(assigner &orig){
    //     this->bus = orig.bus;
    //     this->dom = orig.dom;
    //     this->procN = orig.procN;
    //    }
};

int getDeviceInformation(int *hG, assigner *pr, int cnt)
{
    assigner voy;
    cout << cnt << endl;
    int rb = RLEN;
    cudaGetDeviceCount(&nGpu);
    MPI_Get_processor_name(voy.procN,  &rb);
    int domy, busy, tag=-1, hit=0;

    cout << nGpu << endl;
    cout << ranks << "---------- " << voy.procN << " --------" << endl;
    if (!cnt) hit = 1;

    for (int k=0; k<nGpu; k++)
    {
        cudaGetDeviceProperties(&props, k);
        
        domy = props.pciDomainID;
        busy = props.pciBusID;
        for (int a=0; a<cnt; a++)
        {
            cout << props.name << endl;
            cout << voy.procN << " " << domy << endl;
            cout << pr[a].procN << " " << pr[a].dom << endl;
            
            if (!strcmp(pr[a].procN, voy.procN) && pr[a].dom == domy && pr[a].bus==busy)
            {
                cout << voy.procN << " " << busy << endl;  
                break;  // This GPU is taken.
            }
            cout << a << " " << cnt << endl;
            if (a == (cnt-1))
            {
                hit = 1;
            }
        }
        if (hit)
        {
            tag = k;
            break;
        }
    }

    if (hit)
    { 
        *hG = tag;
        cout << ranks << "  YES GPU!" << endl;
        cout << " " << tag << " "<< props.name << " " << props.multiProcessorCount;
        cout << " " << props.major << "." << props.minor << " " << props.pciDomainID << " " << props.pciBusID << " " << props.pciDeviceID << endl;
        voy.dom = domy;
        voy.bus = busy;
        pr[cnt] = voy;
        return ++cnt;
    }
    else
    {   
        *hG = -1;
        cout << ranks << "  NO GPU!" << endl;
        cout << ranks << " " << voy.procN << " " << endl;
    }
    return cnt;



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
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    //MPI_Status stat;
    MPI_Datatype atype;
    // assigner inuit;
    // inuit.dom = 1111;
    // inuit.bus = 2222;
    // strcpy(inuit.procN, "Pennsylvania");
    assigner ids[nprocs];
    MPI_Datatype typs[] = {MPI_INT, MPI_INT, MPI_CHAR};
    int nm[] = {1, 1, RLEN};
    MPI_Aint disp[] = {0, 4, 8};
    MPI_Type_create_struct(3, nm, disp, typs, &atype);
    MPI_Type_commit(&atype);
    int idz=0;
    int hasGpu;
    if (!ranks) cout << "ranks -- cpuname -- nGpu -- GPU# -- GPUname -- #SM -- CC" << endl;
    for (int k=0; k<nprocs; k++)
    {
        if(ranks == k) 
        {
            idz = getDeviceInformation(&hasGpu, &ids[0], idz);
        }
        MPI_Bcast(&idz, 1, MPI_INT, k, MPI_COMM_WORLD);
        MPI_Bcast(&ids, nprocs, atype, k, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Type_free(&atype);
    MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
}
