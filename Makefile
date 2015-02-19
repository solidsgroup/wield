# Generic Makefile
# Brandon Runnels
# Last Edited: November 5, 2013

include ~/.make.reader
include ~/.make.eigen
include ~/.make.muparser
#include ~/.make.lplib
ifndef EMACS
include ~/.make.color
endif

include .make.local #provides CC, additional defines
CPP_COMPILER_OPTIONS += -c -g3 -ggdb -Wno-deprecated -Wunused-variable 
CPP_LINKER_OPTIONS   += -g3 -ggdb -lpthread -lX11

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
LIB		      = $(LIB_EXT)

.SECONDARY: $(OBJ) $(OBJ_MAIN)

all: make_directories $(EXE)
	@echo -e $(B_ON)$(FG_GREEN)"###"
	@echo "### DONE" 
	@echo -e "###"$(RESET)	

$(PREFIX)bin/%: ./obj/%.o $(OBJ) 
	@echo -e $(B_ON)$(FG_BLUE)"###"
	@echo "### LINKING $@" 
	@echo -e "###"$(RESET)
	@mkdir -p $(dir $@)
	$(CC) ${CPP_LINKER_OPTIONS} -o $@ $^ $(LIB)

./obj/%.o: ./src/%.cpp 
	@echo -e $(B_ON)$(FG_YELLOW)"###"
	@echo "### COMPILING $<" 
	@echo -e "###"$(RESET)
	@mkdir -p $(dir $@)
	$(CC) $(CPP_COMPILER_OPTIONS) $(INC) -o $@ $(PREFIX)$<

./obj/%.o: ./src/%.cc $(HDR)
	@echo -e $(B_ON)$(FG_YELLOW)"###"
	@echo "### COMPILING $<" 
	@echo -e "###"$(RESET)
	$(CC) $(CPP_COMPILER_OPTIONS) $(INC) -o $@ $(PREFIX)$<

make_directories: $(SRC)
	mkdir -p $(dir $(OBJ)) $(dir $(OBJ_MAIN)) bin

%.cpp: $(HDR)

%.cc: $(HDR)

%.h :


#
# Utility Targets
#

clean:
	@echo -e $(B_ON)$(FG_RED)"###"
	@echo "### Cleaning out ./obj, ./bin, *~, *#" 
	@echo -e "###"$(RESET)	
	rm -rf ${OBJ} ${OBJ_MAIN} ${EXE} ./bin/* *~ *\#
tidy:
	rm -rf *~ *\# src/*~ src/*\# dat/*~ dat/*\# inc/*~ inc/*\# 
