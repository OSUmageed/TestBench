# My idea is to wrap make in python and call it over and over in a loop. 
# That way it skips unnecessary builds, but assigns each var in a loop.
# What I'd really like after that is to make the python script run from
# the terminal without any prefix (./ or python). 

# MPICC=$(PREP) mpicc
# MPILD=$(PREP) mpic++
CC = g++
NVCC=$(PREP) nvcc
CONFFILE=eqs.conf
# EQS=$(shell cat $(CONFFILE))
EQS=$(file < $(CONFFILE))

target: 
	$(foreach eq, $(EQS), echo $(eq);)


# NUMBERS = 1 2 3 4
# doit:
#         $(foreach var,$(NUMBERS),./a.out $(var);)

# It will put the compiled programs in the bin subdirectory within the directory
# containing the makefile.
# PROJECTDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
# OUTDIR := $(PROJECTDIR)bin


# GENCODE := -gencode arch=compute_35,code=sm_35 -std=c++11
# PARALLELLIB := -lmpi -Xcompiler -fopenmp 
# NATLIB = -lm -restrict -O3 
# CROSSLIB := -Xptxas=-v 
# INC :=  -I/usr/include/mpi

# CUDAFLAGS := $(GENCODE) $(NATLIB) $(INC) $(CROSSLIB) $(PARALLELLIB) 

# default: $(OUTDIR)/Listofcppfiles

# $(OUTDIR)/Listofcppfiles: cppfile
# 	echo $(*.cpp)