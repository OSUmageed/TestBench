NATLIB := -L$(MPIPATH)/lib -I/usr/include/openmpi-x86_64 -lmpi -lm -std=c++11 -O3

default: ./bin/mpicu ./bin/mpiom

./bin/mpicu: mpi_omp_cuda.cu
	nvcc mpi_omp_cuda.cu -o ./bin/mpicuomp $(NATLIB) -gencode arch=compute_35,code=sm_35

./bin/mpiom: mpi_omp.cpp
	mpic++ mpi_omp.cpp -o ./bin/mpiom $(NATLIB)
