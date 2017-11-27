/*
    Testing creating a custom data type
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>
#include <string>

using namespace std;

#define MPI_R MPI_DOUBLE
#define REAL double

struct real3 {
    double x, y, z;
};

//---------------// 
struct states {
    real3 Q[2]; // Full Step, Midpoint step state variables
    double Pr; // Pressure ratio
};

real3 sq(real3 a)
{
    real3 tmp;
    tmp.x = a.x*a.x;
    tmp.y = a.y*a.y;
    tmp.z = a.z*a.z;
    return tmp;
}

int ranks, nprocs, rpass, rrecv;

void mpi_type(MPI_Datatype *dtype)
{ 
    //double 3 type
    MPI_Datatype vtype;
    MPI_Datatype typs[3] = {MPI_R, MPI_R, MPI_R};
    int n[3] = {1};
    MPI_Aint disp[3] = {0, sizeof(REAL), 2*sizeof(REAL)};

    MPI_Type_create_struct(3, n, disp, typs, &vtype);
    MPI_Type_commit(&vtype);

    int n2[2] = {1, 2};
    MPI_Datatype typs2[2] = {MPI_R, vtype}; 
    MPI_Aint disp2[2] = {0, sizeof(REAL)};

    MPI_Type_create_struct(2, n2, disp2, typs2, dtype);
    MPI_Type_commit(dtype);

    MPI_Type_free(&vtype);
}

void ptype(string when, states* boo)
{
    cout << when << " " << ranks << " ";
    for (int k=0; k<2; k++)
    {
        cout << boo[k].Q[0].x << " " << boo[k].Q[0].y << " " << boo[k].Q[0].z << " " << boo[k].Pr << " ";
    }
    cout << " BOOM " << endl;
}

int main(int argc, char *argv[])
{
    
    MPI_Datatype state_type;
    MPI_Request req;

    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &ranks);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    
    mpi_type(&state_type);
    rpass = ranks+1 % nprocs;
    rrecv = ranks-1 % nprocs;
    real3 odd = {11, 13, 15};
    real3 even = {4, 6, 8};
    states st[1];

    st[0].Q[0] = (ranks & 1) ? odd : even;
    st[0].Q[1] = sq(st[0].Q[0]);
    st[0].Pr = ranks;

    ptype("Before", &st[0]);

    MPI_Isend(&st[0], 1, state_type, rpass, 0, MPI_COMM_WORLD, &req);

    MPI_Recv(&st[1], 1, state_type, rrecv, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    ptype("After", &st[0]);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Request_free(&req);
    MPI_Finalize();
    return 0;
}

