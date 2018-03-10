# Simple makefile for all test problems for 1D Swept Rule

# LDFLAGS := -lglut -lGL -lGLU -lGLEW

# It will put the compiled programs in the bin subdirectory within the directory
# containing the makefile

PROJECT_DIR=$(shell pwd)
EQPATH:=$(abspath equations)
IC:=$(firstword $(INC))

INC_PARAMS=$(INC:%=-I%)

EQA:=$(wildcard $(EQPATH)/*.h)

EQB:=$(filter-out $(EQPATH)/eqHead.h, $(EQA))

EQC:=$(foreach eq, $(EQB), $(basename $(notdir $(eq))))

OBJS:=$(foreach eq, $(EQC), $(LIB_DIR)/$(eq).o)

.PHONY: obj all 

all: $(OBJS)

$(OBJS): kernel.cu
	nvcc -c $^ -o $@ -D$(*F)=1 $(CUDAFLAGS) $(INC_PARAMS) 
	@echo "DONE"

# kern.o: kernel.cu $(IC)/jsoncpp.cpp
# 	nvcc $^ -o $@  $(CUDAFLAGS) $(INC_PARAMS) 

# -include $(EQB)