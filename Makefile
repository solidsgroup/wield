# Generic Makefile
# Brandon Runnels
# Last Edited: November 5, 2013

RESET              = '\033[0m'
B_ON               = '\033[1m'
FG_RED             = '\033[31m'
FG_GREEN           = '\033[32m'
FG_YELLOW          = '\033[33m'
FG_BLUE            = '\033[34m'

CC                    = g++	
CPP_COMPILER_OPTIONS += -c -g3 -ggdb -fopenmp -Wno-deprecated -Wunused-variable -DMUPARSER 
CPP_LINKER_OPTIONS   += -g3 -ggdb -fopenmp -lX11 

ifdef EMACS
PREFIX                = $(shell pwd)/
endif
EXCLUDE               = $(PREFIX)/src/MainOld.cpp
SRC_MAIN              = $(filter-out $(EXCLUDE), $(shell find ./src/ -name '*.cc'))
EXE 		      = $(subst ./src/,./bin/, $(SRC_MAIN:.cc=))
SRC		      = $(filter-out $(EXCLUDE), $(shell find ./src/ -name '*.cpp'))
HDR		      = $(filter-out $(EXCLUDE), $(shell find ./inc/ ./src/ -name '*.h'))
OBJ 		      = $(subst ./src/,./obj/, $(SRC:.cpp=.o)) 
OBJ_MAIN              = $(subst ./src/,./obj/, $(SRC_MAIN:.cc=.o))
INC 		      = -I./src \
		        -I./inc \
		        $(INC_EXT)
LIB		      = $(LIB_EXT) -lmuparser

.SECONDARY: $(OBJ) $(OBJ_MAIN)

all: make_directories $(EXE)
	@echo $(B_ON)$(FG_GREEN)"###"
	@echo "### DONE" 
	@echo "###"$(RESET)	

$(PREFIX)bin/%: ./obj/%.o $(OBJ) 
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
	mkdir -p $(dir $(OBJ)) $(dir $(OBJ_MAIN)) bin

%.cpp: $(HDR)

%.cc: $(HDR)

%.h :

#
# Unit Tests
#
TEST_DIRS = $(shell find tests -mindepth 1 -type d)

test: $(TEST_DIRS:=/output.dat)
%/output.dat: .FORCE
	-@python3 scripts/unittest.py $(@:output.dat=)
.FORCE:


#
# Utility Targets
#

clean:
	@echo $(B_ON)$(FG_RED)"###"
	@echo "### Cleaning out ./obj, ./bin, *~, *#" 
	@echo "###"$(RESET)	
	rm -rf ${OBJ} ${OBJ_MAIN} ${EXE} ./bin/* *~ *\#
tidy:
	rm -rf *~ *\# src/*~ src/*\# dat/*~ dat/*\# inc/*~ inc/*\# 
