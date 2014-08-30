CXX=g++
CXXFLAGS=
LDFLAGS=
LDLIBS=

SRC=src/volcano.cc
OBJ=$(SRC:.cc=.o)

volcano: $(OBJ) 
	$(info src = $(SRC))
	$(info obj = $(OBJ))
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) 


