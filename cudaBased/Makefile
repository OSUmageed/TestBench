CUDAF := -gencode arch=compute_35,code=sm_35 -w -O3 --std=c++11
LP := $(MPIPATH)/lib
ILP := $(INTELLIB)
IP := $(MPIPATH)/include
XL := -Xlinker=-rpath,$(LP) -Xlinker=-rpath,$(ILP) 
LIBF := -I$(IP) -I$(CUDAPATH)/include -L$(CUDAPATH)/lib64 -L$(LP) -L$(ILP) -lm -lmpich -lopa -lmpl -lrt -lpthread

defualt: ./bin/gpuD ./bin/newgpuD

./bin/gpuD: gpuDetect.cu Makefile
	$(CUDAPATH)/bin/nvcc gpuDetect.cu -o ./bin/gpuD $(CUDAF) $(LIBF) $(XL) 

./bin/newgpuD: gpuDetectNext.cu Makefile
	$(CUDAPATH)/bin/nvcc gpuDetectNext.cu -o ./bin/newgpuD $(CUDAF) $(LIBF) $(XL)

#echo `ls bin`
