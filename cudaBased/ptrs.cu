#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>

// nvcc ptrs.cu -o ./bin/ptrs -gencode arch=compute_35,code=sm_35 -lm -O3 -std=c++11

using namespace std;

__device__ int *a, *b; 

__global__ void setptr(int *sj, int offs, int *ps)
{
	ps = &sj[offs];
}


__global__ void someMth(int *sj)
{
	int gid = blockDim.x * blockIdx.x + threadIdx.x; //Global Thread ID
	int om = sj[gid+1];
	sj[gid] += om;
}

int main()
{
	int *fptr, *sptr;
	int mysize = 256;
	int realsz = mysize/2;
	int tpb = 32;
	int bks = realsz/tpb;	
	int rlsz = sizeof(int)*realsz;
	int imem[mysize];
	int rmem[mysize]; 
	int gmem[mysize]; 

	cudaMalloc((void **) &fptr, sizeof(int)*mysize);
	for (int k=0; k<mysize; k++) imem[k] = k;

	cudaMemcpy(fptr, &imem, sizeof(int) * mysize, cudaMemcpyHostToDevice);

	someMth <<< bks, tpb >>> (fptr);

    cudaMemcpy(&imem, fptr, rlsz, cudaMemcpyDeviceToHost);

//	for (int k=0; k<realsz; k++) cout << imem[k] << " ";
//	cout << endl;

	setptr <<< 1,1 >>> (fptr, tpb, sptr); 

	someMth <<< bks, tpb  >>> (fptr+tpb);

	cudaMemcpy(&rmem, fptr, rlsz+sizeof(int)*tpb, cudaMemcpyDeviceToHost);
	cudaMemcpy(&gmem, fptr + (tpb*2), rlsz+sizeof(int)*tpb, cudaMemcpyDeviceToHost);

	cout << "IDx || After 1 || Swap" << endl;
	for (int k=0; k<realsz + tpb; k++) cout << k << " " << imem[k] << " " << rmem[k] << " " << gmem[k] << endl;

	return 0;
}
