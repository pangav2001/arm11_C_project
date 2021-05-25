CC      = gcc
CFLAGS  = -Wall -g -std=c99 -Werror -pedantic
LIBS = -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: assemble.o


#Build the emulator executable
emulate: memory.o registers.o

#Build the object files for emulator
memory.o: memory.h
registers.o: registers.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
