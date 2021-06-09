CC      = gcc
CFLAGS  = -Wall -g #-std=c99 -Werror -pedantic // is making the mnemonic array throw error saying it's not used :/, also cannot use c99 standard for strtok
LIBS = -lm
LDFLAGS = -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate


#Build the assembler executable
assemble: assemble.o multiply.o tokenizer.o 

tokenizer.o: tokenizer.h


#Build the emulator executable
emulate: emulate.o

#Build the object files for emulator
multiply.o : multiply.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
