#ifndef MUL_ASS
#define MUL_ASS

#include "tokenizer.h"
#include "emulate_src/registers.h"
#include <stdint.h>



// mul, Rd, Rm, Rs
// mla Rd, Rm, Rs, Rn
uint32_t multiply(enum Mnemonic instruction, char *rd_string, char *rm_string, char *rs_string, ...);

#endif