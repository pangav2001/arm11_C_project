CC      = gcc
CFLAGS  = -Wall -g -Werror -pedantic
BUILD = memory.o registers.o parse_file.o decode.o data_processing.o flags.o multiply.o branch.o single_data_transfer.o emulate_output.o

.SUFFIXES: .c .o

.PHONY: all clean

all: $(BUILD)


#Build the object files for emulator
memory.o: headers/memory.h
registers.o: headers/registers.h
parse_file.o: headers/parse_file.h
decode.o: headers/decode.h
data_processing.o: headers/data_processing.h
flags.o: headers/flags.h
multiply.o: headers/multiply.h
branch.o: headers/branch.h
single_data_transfer.o: headers/single_data_transfer.h
emulate_output.o: headers/emulate_output.h

clean:
	rm -f $(wildcard *.o)
