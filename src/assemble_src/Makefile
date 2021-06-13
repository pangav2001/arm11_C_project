CC      = gcc
CFLAGS  = -Wall -g -Werror -pedantic
LIB = libassemble.a
LIBOBJS = assemble.o
BUILD = $(LIB)

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD)


$(LIB):	$(LIBOBJS)
	ar rcs $(LIB) $(LIBOBJS)


#Build the assembler executable
assemble.o: assemble.o multiply.o tokenizer.o data_processing.o branch.o hash_table.o output.o sdt_assembly.o


#Build the object files for assembler
tokenizer.o: tokenizer.h
multiply.o: multiply.h
data_processing.o: data_processing.h
branch.o: branch.h
hash_table.o: hash_table.h
output.o: output.h
sdt_assembly.o: sdt_assembly.h


clean:
	rm -f $(wildcard *.o)
	rm -f $(wildcard *.a)
	rm -f assemble
	rm -f tst
