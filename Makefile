COMPILER?=g++
CFLAGS=-Wall -pedantic-errors -std=c++1z -O0 -g -ggdb -I ./inc
BINDIR=./bin
SRC=./src
SRC_FILES=$(wildcard $(SRC)/*.cpp)
BIN_EXE=$(patsubst $(SRC)%, $(BINDIR)%, $(SRC_FILES))
OBJS=$(BIN_EXE:.cpp=.o)

all: $(OBJS) linking

$(BINDIR)/%.o: $(SRC)/%.cpp
	@$(COMPILER) $(CFLAGS) -c -o $@ $< 
	@echo [CXX] $@
	
linking:
	@$(COMPILER) $(OBJS) -o ./bin/simple-assembler.out
#	@rm ./bin/*.o
	
clean:
	@rm -rf $(BINDIR)/*

