#ifndef MUL_ASS
#define MUL_ASS

#include "tokenizer.h"
#include "emulate_src/registers.h"
#include <stdint.h>

uint32_t multiply(enum Mnemonic instruction, enum Register_Names rd, enum Register_Names rm, enum Register_Names rs, enum Register_Names rn);

#endif