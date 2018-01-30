CUDAF := -gencode arch=compute_35,code=sm_35 -w -O3 --std=c++11
include conf
NVCC=$(shell which nvcc)
# LP := $(MPIPATH)/lib
# ILP := $(INTELLIB)
# IP := $(MPIPATH)/include
# XL := -Xlinker=-rpath,$(LP) -Xlinker=-rpath,$(ILP) 
# LIBS := -I$(IP) -I$(CUDAPATH)/include -L$(CUDAPATH)/lib64 -L$(LP) -L$(ILP) -lm -lmpich -lopa -lmpl -lrt -lpthread

defualt: ./bin/gpuD ./bin/newgpuD

./bin/gpuD: gpuDetect.cu Makefile
	$(NVCC) gpuDetect.cu -o ./bin/gpuD $(CUDAF) $(IPATH) $(LPATH) $(LIBS) $(XL) 

./bin/newgpuD: gpuDetectNext.cu Makefile
	$(NVCC) gpuDetectNext.cu -o ./bin/newgpuD $(CUDAF) $(IPATH) $(LPATH) $(LIBS) $(XL)
