#Makefile

CC = gcc
CFLAGS = -Wall -g -Werror -pedantic
BUILD = pacman

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD)

pacman: actors.o gameview.o ghost_movement.o pacman_movement.o

actors.o: actors.h
gameview.o: gameview.h
ghost_movement.o: ghost_movement.h
pacman_movement.o: pacman_movement.h

clean:
	rm -f $(wildcard *.o)
	rm -f pacman