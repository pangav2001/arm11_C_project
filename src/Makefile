CC      = gcc
CFLAGS  = -Wall -g -Werror -pedantic -Ilib
LDLIBS = -Llib -lemulate -lassemble
BUILD = libassemble libemulate assemble emulate

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD)



clean:
	/bin/rm -f $(BUILD) *.o core
	cd assemble_src; make clean
	cd emulate_src; make clean

libassemble:
	cd assemble_src; make

libemulate:
	cd emulate_src; make

assemble: assemble.o

emulate: emulate.o

assemble.o: 
