#ifndef _DATA_PROCESSING_H_ASSEMBLER_
#define _DATA_PROCESSING_H_ASSEMBLER_

#include "tokenizer.h"
#include "../../emulate_src/headers/decode.h"
#include <stdint.h>



// <and, eor, sub, rsb, add, orr>, Rd, Rn, Operand2
// <mov>, Rd, Operand2
// <tst, teq, cmp> Rn, Operand2
uint32_t data_process(tokens_t *instructions);

uint8_t calculate_register_shift(char *epxression);

#define SET_BITS(NUM, LSB, VAL) (NUM) |= (VAL) << (LSB)

#endif