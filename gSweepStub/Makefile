# Simple makefile for all test problems for gSweep

CODE_DIR:=oneD # twoD

export BIN_DIR:=$(abspath bin)
export LIB_DIR:=$(BIN_DIR)/lib

export NVCC:=$(shell which nvcc) 
INN:=utilities $(CODE_DIR)
export INC:=$(foreach ipath, $(INN), $(abspath $(ipath)))
CCFLAGS:= -lm -O3 --std=c++11 -w
export CUDAFLAGS = -gencode arch=compute_60,code=sm_60  -restrict --ptxas-options=-v  $(CCFLAGS)
IC=$(firstword $(INC))
JS:=$(LIB_DIR)/jsons.so
GMAIN:=$(LIB_DIR)/main.so

vpath %.o $(LIB_DIR)
vpath %.so $(LIB_DIR)

.PHONY: echoes  #$(EXECUTABLES)

# $(EXECUTABLES): %: $(OUT_DIR)/%.so 
# 	$(NVCC) $^ -o $(OUT_DIR)/$@ 

$(OUT_DIR)/%: swepts $(JS) $(LIB_DIR)/%.o
	$(NVCC) -o $@ $^ $(CUDAFLAGS) 

$(GMAIN): gsmain.cpp
	g++ $(CCFLAGS) -c $^ -o $@ -I$(IC) -lcudart -lcuda

swepts:
	ls $(OUT_DIR)
	$(MAKE) -C $(CODE_DIR)

echoes:
	@echo $(OUT_DIR) $(IN)

$(JS): $(INC)/jsoncpp.cpp
	g++ $(CCFLAGS) -c $^ -o $@



# main.o: gsmain.cpp $(CODE_DIR)/kernel.h $(CODE_DIR)/equation.h
# 	$(NVCC) $< -o $(OUT_DIR)/$@ $(CUDAFLAGS) -I$(INC) 

# build:
#     @mkdir -p bin

# clean:
