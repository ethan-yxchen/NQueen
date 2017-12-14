CC=g++
CFLAGS=-Wall --std=c++11 -msse4.2 -lstdc++ -lm -O3 -I.

nqueen: *.cpp *.h NQueenBacktrack.o
	$(CC) -o nqueen $(CFLAGS) nqueen.cpp NQueenBacktrack.o

NQueenBacktrack.o:  NQueenBacktrack.cpp NQueenBacktrack.h
	$(CC) $(CFLAGS) -c NQueenBacktrack.cpp

all: nqueen
