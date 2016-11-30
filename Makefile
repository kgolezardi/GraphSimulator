all: Graphics.o Graph.o main.cpp
	g++ main.cpp Graphics.o Graph.o -o main -O2 -lSDL2 -lSDL2_gfx

test: Graphics.o test.cpp
	g++ test.cpp Graphics.o -lSDL2 -lSDL2_gfx

Graphics.o: Graphics.cpp Graphics.h
	g++ -c Graphics.cpp

Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp

