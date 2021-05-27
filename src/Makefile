CC      = gcc
CFLAGS  = -Wall -g -std=c99 -pedantic
LIBS = -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble: assemble.o


#Build the emulator executable
emulate: memory.o registers.o parse_file.o decode.o data_processing.o flags.o multiply.o branch.o #single_data_transfer.o#

#Build the object files for emulator
memory.o: memory.h
registers.o: registers.h
parse_file.o: parse_file.h
decode.o: decode.h
data_processing.o: data_processing.h
flags.o: flags.h
multiply.o: multiply.h
branch.o: branch.h
#single_data_transfer.o: single_data_transfer.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
