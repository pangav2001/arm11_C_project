
#ifndef single_data_transfer_assembly
#define single_data_transfer_assembly

#include <stdint.h>
#include "tokenizer.h"
#include "emulate_src/registers.h"
#include "emulate_src/memory.h"

uint32_t sdt_assembly(enum Mnemonic instruction, enum Register_Names rd, uint16_t address);

#endif