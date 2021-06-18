#Makefile

CC = gcc
CFLAGS = -Wall -g -Werror -Wextra -pedantic
BUILD = game test

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD)

game: ghosts.o map.o pacman.o -lncursesw

test:
	cd test; make

priority_queue.o: headers/priority_queue.h
ghosts.o : headers/ghosts.h 
map.o: headers/map.h
pacman.o: headers/pacman.h

clean:
	cd test; make clean
	rm -f $(wildcard *.o)
	rm -f game
	rm -f dijkstra
