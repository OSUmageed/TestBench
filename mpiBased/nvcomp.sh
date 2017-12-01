nvcc mpi_omp_cuda.cu -o ./bin/mpicuomp -gencode arch=compute_35,code=sm_35 -LMPIPATH/bin -I/usr/include/mpi -lmpi -lm --std=c++11 -O3 
