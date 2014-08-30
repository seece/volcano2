CXX=g++
CXXFLAGS=-g -O0 -Wall -Wno-write-strings -Wno-deprecated-declarations -fpermissive
LDFLAGS=-lmikmod
LDLIBS=
SRC=src/volcano.cc src/sound.cc
OBJ=$(SRC:.cc=.o)

volcano: $(OBJ) 
	$(info src = $(SRC))
	$(info obj = $(OBJ))
	$(CXX) $(OBJ) -o $@ `allegro-config --cflags --libs` $(LDFLAGS) 

clean:
	rm -f $(OBJ)
	rm -f volcano

run: volcano
	cp volcano game/volcano
	(cd game && ./volcano)

.PHONY : clean
.PHONY : run
