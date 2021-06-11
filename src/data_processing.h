#ifndef DP_ASS
#define DP_ASS

#include "tokenizer.h"
#include "emulate_src/registers.h"
#include <stdint.h>



// <and, eor, sub, rsb, add, orr>, Rd, Rn, Operand2
// <mov>, Rd, Operand2
// <tst, teq, cmp> Rn, Operand2
uint32_t data_process(tokens_t *instructions);

#endif