CXX=g++
CXXFLAGS=-Wall -Wno-write-strings -Wno-deprecated-declarations -fpermissive
LDFLAGS=
LDLIBS=

SRC=src/volcano.cc
OBJ=$(SRC:.cc=.o)

volcano: $(OBJ) 
	$(info src = $(SRC))
	$(info obj = $(OBJ))
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) 


