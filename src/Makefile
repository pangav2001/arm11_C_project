CC      = gcc
CFLAGS  = -Wall -g -Werror -Wextra -pedantic -O3
BUILD = libassemble libemulate assemble emulate
ASS_BUILD = assemble_src/multiply.o assemble_src/tokenizer.o	assemble_src/data_processing.o assemble_src/branch.o assemble_src/hash_table.o assemble_src/output.o assemble_src/sdt_assembly.o
EMU_BUILD = emulate_src/memory.o emulate_src/registers.o emulate_src/parse_file.o emulate_src/decode.o emulate_src/data_processing.o emulate_src/flags.o emulate_src/multiply.o emulate_src/branch.o emulate_src/single_data_transfer.o emulate_src/emulate_output.o


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

assemble: $(ASS_BUILD)

emulate: $(EMU_BUILD)