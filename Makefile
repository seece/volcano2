CXX=g++
CXXFLAGS=-std=c++11 -g -O0 -Wall -Wno-write-strings -Wno-deprecated-declarations -fpermissive
LDFLAGS=`allegro-config --cflags --libs` `libmikmod-config --cflags --libs`
LDLIBS=
SRC=src/volcano.cc src/sound.cc
OBJ=$(SRC:.cc=.o)

volcano: $(OBJ) 
	$(info src = $(SRC))
	$(info obj = $(OBJ))
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) 

clean:
	rm -f $(OBJ)
	rm -f volcano
	rm -f game/volcano

game/volcano: volcano
	cp volcano game/volcano

run: game/volcano
	(cd game && ./volcano)

gdb: game/volcano
	(cd game && gdb ./volcano)

.PHONY : clean
.PHONY : run
.PHONY : gdb
