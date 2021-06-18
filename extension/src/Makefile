#Makefile

CC = gcc
CFLAGS = -Wall -g -Werror -pedantic
BUILD = game

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD)

game: ghosts.o map.o pacman.o -lncursesw

priority_queue.o: priority_queue.h
ghosts.o : ghosts.h 
map.o: map.h
pacman.o: pacman.h

clean:
	rm -f $(wildcard *.o)
	rm -f game
	rm -f dijkstra
