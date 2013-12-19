
#include ~/.make.eureka
include ~/.make.eigen
include ~/.make.color
include ~/.make.matio

CC              = g++
CPP_COMPILER_OPTIONS = -std=c++11
CPP_LINKER_OPTIONS = -lm -lmuparser -lreadline

EXE 		= ./bin/Main
SRC		= $(shell find ./src/ -name '*.cpp')
HDR		= $(shell find ./inc/ -name '*.h')
OBJ 		= $(subst ./src/,./obj/, $(SRC:.cpp=.o))
INC 		= -I./src \
		  -I./inc \
		  $(INC_EXT)
LIB		= $(LIB_EXT)


all: make_directories $(EXE)

make_directories:
	@mkdir -p $(dir $(OBJ))

$(EXE): $(OBJ)
	@echo -e $(B_ON)$(FG_BLUE)"###"
	@echo "### LINKING" 
	@echo -e "###"$(RESET)
	$(CC) ${CPP_LINKER_OPTIONS} -o $(EXE) $(OBJ) $(LIB)
	@echo -e $(B_ON)$(FG_GREEN)"###"
	@echo "### DONE" 
	@echo -e "###"$(RESET)	

obj/%.o: src/%.cpp #$(HDR)
	@echo -e $(B_ON)$(FG_YELLOW)"###"
	@echo "### COMPILING $<" 
	@echo -e "###"$(RESET)
	$(CC) -c $(CPP_COMPILER_OPTIONS) $(INC) -o $@ $<

%.cpp:

%.h :


#
# Utility Targets
#

clean:
	@echo -e $(B_ON)$(FG_RED)"###"
	@echo "### Cleaning out ./obj, ./bin, *~, *#" 
	@echo -e "###"$(RESET)	
	rm -rf ${OBJ}  ${EXE} *~ *\#
tidy:
	rm -rf *~ *\# src/*~ src/*\# dat/*~ dat/*\# inc/*~ inc/*\# 
