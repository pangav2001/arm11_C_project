CC      = gcc
CFLAGS  = -Wall -g -Werror -pedantic
BUILD = multiply.o tokenizer.o data_processing.o branch.o hash_table.o output.o sdt_assembly.o

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD)


#Build the object files for assembler
tokenizer.o: headers/tokenizer.h
multiply.o: headers/multiply.h
data_processing.o: headers/data_processing.h
branch.o: headers/branch.h
hash_table.o: headers/hash_table.h
output.o: headers/output.h
sdt_assembly.o: headers/sdt_assembly.h


clean:
	rm -f $(wildcard *.o)
	rm -f tst
