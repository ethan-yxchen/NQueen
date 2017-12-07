CC=gcc
CFLAGS=-Wall --std=c++11 -msse4.2 -lstdc++ -lm -O3 -I.

nqueen: *.cpp *.h
	$(CC) -o nqueen $(CFLAGS) nqueen.cpp

all: nqueen
