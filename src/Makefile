CC      = gcc
CFLAGS  = -Wall -g #-std=c99 -Werror -pedantic // is making the mnemonic array throw error saying it's not used :/, also cannot use c99 standard for strtok
LIBS = -lm
LDFLAGS = -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble #emulate


#Build the assembler executable
assemble: assemble.o multiply.o tokenizer.o data_processing.o branch.o hash_table.o

tokenizer.o: tokenizer.h

multiply.o: multiply.h

data_processing.o: data_processing.h

branch.o: branch.h

hash_table.o: hash_table.h


#Build the emulator executable
#emulate: emulate.o

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
