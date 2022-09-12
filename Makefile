# Generic Makefile
# Brandon Runnels

RESET              = '\033[0m'
B_ON               = '\033[1m'
FG_RED             = '\033[31m'
FG_GREEN           = '\033[32m'
FG_YELLOW          = '\033[33m'
FG_BLUE            = '\033[34m'

CC                    = g++	
CPP_COMPILER_OPTIONS += -c -g3 -ggdb -fopenmp -Wno-deprecated -Wunused-variable -DMUPARSER 
CPP_LINKER_OPTIONS   += -g3 -ggdb -fopenmp  

INC_PYTHON            = $(shell python3-config --cflags)
LIB_PYTHON            = $(shell python3-config --ldflags)
PYTHON_NAME           = py/wield$(shell python3-config --extension-suffix)

ifdef EMACS
PREFIX                = $(shell pwd)/
endif
EXCLUDE               = $(PREFIX)/src/MainOld.cpp
SRC_MAIN              = $(filter-out $(EXCLUDE), $(shell find ./src/ -name '*.cc'))
EXE 		      = bin/wield
SRC		      = $(filter-out $(EXCLUDE), $(shell find ./src/ -mindepth 2 -name  '*.cpp'))
HDR		      = $(filter-out $(EXCLUDE), $(shell find ./inc/ ./src/ -name '*.h'))
OBJ 		      = $(subst ./src/,./obj/, $(SRC:.cpp=.o)) 
OBJ_MAIN              = $(subst ./src/,./obj/, $(SRC_MAIN:.cc=.o))
INC 		      = -O3 -I./src \
		        -I./inc \
			-I./extern/eigen/
LIB		      = $(LIB_EXT) -lmuparser 


.SECONDARY: $(OBJ) $(OBJ_MAIN)

default: make_directories $(EXE)

all: make_directories $(EXE) python
	@echo $(B_ON)$(FG_GREEN)"###"
	@echo "### DONE" 
	@echo "###"$(RESET)	

python: make_directories $(PYTHON_NAME)
	@echo $(B_ON)$(FG_GREEN)"###"
	@echo "### DONE" 
	@echo "###"$(RESET)	

$(PYTHON_NAME): ./py/python.cpp $(OBJ) $(SRC) $(HDR)
	@echo $(B_ON)$(FG_BLUE)"###"
	@echo "### LINKING $@" 
	@echo "###"$(RESET)
	$(CC) -DWIELD_PYTHON $(INC) -I./extern/pybind11/include/ -O3 -Wall -shared -std=c++11 -fPIC $(INC_PYTHON) py/python.cpp -o $@

bin/wield: ./obj/wield.o $(OBJ) 
	@echo $(B_ON)$(FG_BLUE)"###"
	@echo "### LINKING $@" 
	@echo "###"$(RESET)
	@mkdir -p $(dir $@)
	$(CC) ${CPP_LINKER_OPTIONS} -o $@ $^ $(LIB)

./obj/%.o: ./src/%.cpp 
	@echo $(B_ON)$(FG_YELLOW)"###"
	@echo "### COMPILING $<" 
	@echo "###"$(RESET)
	@mkdir -p $(dir $@)
	$(CC) $(CPP_COMPILER_OPTIONS) $(INC) -o $@ $(PREFIX)$<

./obj/%.o: ./src/%.cc $(HDR)
	@echo $(B_ON)$(FG_YELLOW)"###"
	@echo "### COMPILING $<" 
	@echo "###"$(RESET)
	$(CC) $(CPP_COMPILER_OPTIONS) $(INC) -o $@ $(PREFIX)$<

make_directories: $(SRC)
	git submodule update --init --recursive
	mkdir -p $(dir $(OBJ)) $(dir $(OBJ_MAIN)) bin

%.cpp: $(HDR)

%.cc: $(HDR)

%.h :

#
# Unit Tests
#
test: test-csl test-energy1d

TEST_DIRS_CSL = $(shell find tests -mindepth 1 -type d -name "csl*"| sort)
test-csl: $(TEST_DIRS_CSL:=/output.dat)

TEST_DIRS_ENERGY1D = $(shell find tests -mindepth 1 -type d -name "energy1d*"| sort)
test-energy1d: $(TEST_DIRS_ENERGY1D:=/output.dat)

%/output.dat: .FORCE
	-@python3 scripts/unit_test.py $(@:output.dat=)
.FORCE:


#
# Utility Targets
#

clean:
	@echo $(B_ON)$(FG_RED)"###"
	@echo "### Cleaning out ./obj, ./bin, *~, *#" 
	@echo "###"$(RESET)	
	rm -rf ${OBJ} ${OBJ_MAIN} ${EXE} ./bin/* *~ *\# $(PYTHON_NAME)
tidy:
	rm -rf *~ *\# src/*~ src/*\# dat/*~ dat/*\# inc/*~ inc/*\# 
