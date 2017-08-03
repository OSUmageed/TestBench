
MPICC=$(PREP) mpicc
MPILD=$(PREP) mpic++
NVCC=$(PREP) nvcc

# It will put the compiled programs in the bin subdirectory within the directory
# containing the makefile
PROJECTDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
OUTDIR := $(PROJECTDIR)bin


GENCODE := -gencode arch=compute_35,code=sm_35 -std=c++11
PARALLELLIB := -lmpi -Xcompiler -fopenmp 
NATLIB = -lm -restrict -O3 
CROSSLIB := -Xptxas=-v 
INC :=  -I/usr/include/mpi

CUDAFLAGS := $(GENCODE) $(NATLIB) $(INC) $(CROSSLIB) $(PARALLELLIB) 

default: $(OUTDIR)/Listofcppfiles

$(OUTDIR)/Listofcppfiles: cppfile
	filesandflags
