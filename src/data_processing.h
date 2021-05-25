#include "registers.h"
#include "memory.h"
#include "flags.h"
#include "decode.h"
#include <stdint.h>

#ifndef DATA_PROCESSING
#define DATA_PROCESSING

enum Operators
{
    AND,
    EOR,
    SUB,
    RSB,
    ADD,
    TST = 8,
    TEQ,
    CMP,
    ORR = 12,
    MOV
};

void process_func(int8_t i_flag, enum Operators opcode, int8_t s_flag, enum Register_Names rn, enum Register_Names rd, int16_t operand2);

int32_t immediate_operand(int16_t operand2, int8_t i_flag);

#endif