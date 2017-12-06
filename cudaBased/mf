CUDAF := -gencode arch=compute_35,code=sm_35 -w --ptxas-options=-v
LP := $(MPIPATH)/lib
ILP := $(INTELLIB)
IP := $(MPIPATH)/include
XL := -Xlinker=-rpath,$(LP) -Xlinker=-rpath,$(ILP) 
LIBF := -I$(IP) -L$(LP) -L$(ILP) -lm -lmpi

defualt: ./bin/gpuD

./bin/gpuD: gpuDetect.cu
	nvcc gpuDetect.cu -o ./bin/gpuD $(CUDAF) $(LIBF) $(XL) 

#echo `ls bin`
