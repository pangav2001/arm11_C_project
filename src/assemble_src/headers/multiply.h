#ifndef MUL_ASS
#define MUL_ASS

#include "tokenizer.h"
#include "../../emulate_src/headers/registers.h"
#include <stdint.h>



// mul, Rd, Rm, Rs
// mla Rd, Rm, Rs, Rn
uint32_t assemble_multiply(tokens_t *instructions);

#endif