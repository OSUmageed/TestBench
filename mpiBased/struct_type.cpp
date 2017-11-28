/*
    Testing creating a custom data type
*/

//mpic++ struct_type.cpp -o./bin/stype -O3 -lm
// mpirun -np 4 ./stype

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>
#include <string.h>

using namespace std;

#define MPI_R MPI_DOUBLE
#define REAL double

struct real3 {
    double x, y, z;
};

//---------------// 
struct states {
    real3 Q[2]; // Full Step, Midpoint step state variables
    REAL Pr; // Pressure ratio
};

real3 sq(real3 a)
{
    real3 tmp;
    tmp.x = a.x*a.x;
    tmp.y = a.y*a.y;
    tmp.z = a.z*a.z;
    return tmp;
}

int ranks, nprocs, rpass, rrecv, sz;

void mpi_type(MPI_Datatype *dtype)
{ 
    //double 3 type
    states state_ex;
    MPI_Datatype vtype;
    MPI_Datatype typs[3] = {MPI_R, MPI_R, MPI_R};
    int n[] = {1, 1, 1};
    MPI_Aint disp[] = {0, sizeof(REAL), 2*sizeof(REAL)};

    MPI_Type_create_struct(3, n, disp, typs, &vtype);
    MPI_Type_commit(&vtype);

    int n2[2] = {2, 1};
    MPI_Datatype typs2[2] = {vtype, MPI_R}; 
    MPI_Aint disp2[2] = {0, 6*sizeof(REAL)};
    // disp2[0] = &state_ex.Q[0] - &state_ex;
    // disp2[1] = &state_ex.Pr - &state_ex;

    MPI_Type_create_struct(2, n2, disp2, typs2, dtype);
    MPI_Type_commit(dtype);

    MPI_Type_free(&vtype);
}

void ptype(states* boo)
{
    for (int k=0; k<2; k++)
    {
        printf("%d, %d: ", ranks, k);
        for (int n=0; n<2; n++)
        {
            printf("%.2f %.2f %.2f %.2f \n", boo[k].Q[n].x, boo[k].Q[n].y, boo[k].Q[n].z, boo[k].Pr);
        }
    }
}

int main(int argc, char *argv[])
{
    MPI_Datatype state_type;
    MPI_Request req;
    MPI_Status stat;

    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &ranks);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    
    mpi_type(&state_type);
    rpass = (ranks+1 == nprocs) ? 0 : ranks+1;
    rrecv = (ranks-1 < 0) ? nprocs-1 : ranks-1;

    MPI_Type_size(state_type, &sz);
    printf("%d, %d\n", ranks, sz);

    real3 odd = {11.2, 13.2, 15.2};
    real3 even = {4.1, 6.1, 8.1};
    states st[1];

    st[0].Q[0] = (ranks & 1) ? odd : even;
    st[0].Q[1] = sq(st[0].Q[0]);
    st[0].Pr = (double)ranks;

    st[1] = st[0];

    MPI_Barrier(MPI_COMM_WORLD);

    if (!ranks) printf("Me, Pass, Recev\n");

    MPI_Barrier(MPI_COMM_WORLD);

    printf("%d %d %d\n", ranks, rpass, rrecv);

    MPI_Barrier(MPI_COMM_WORLD);

    sleep(1);

    if (!ranks) cout << "------------ BEFORE" << endl;

    sleep(1);

    MPI_Barrier(MPI_COMM_WORLD);

    ptype(&st[0]);

    MPI_Barrier(MPI_COMM_WORLD);

    sleep(1);
    
    MPI_Isend(&st[0], 1, state_type, rpass, 0, MPI_COMM_WORLD, &req);

    MPI_Recv(&st[1], 1, state_type, rrecv, 0, MPI_COMM_WORLD, &stat);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Wait(&req, &stat);

    sleep(1);

    if (!ranks) cout << "------------ AFTER:" << endl;

    fflush(stdout);

    MPI_Barrier(MPI_COMM_WORLD);

    sleep(1);

    ptype(&st[0]);

    fflush(stdout);

    sleep(1);

    // MPI_Request_free(&req);

    MPI_Barrier(MPI_COMM_WORLD);
    

    cout << "Free Request " << ranks << endl;

    MPI_Type_free(&state_type);

    cout << "Free Type " << ranks << endl;

    MPI_Barrier(MPI_COMM_WORLD);

    sleep(1);

    fflush(stdout);

    MPI_Finalize();

    return 0;
}

