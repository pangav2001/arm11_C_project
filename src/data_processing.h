#include "registers.h"
#include "memory.h"
#include "flags.h"
#include "decode.h"
#include <stdint.h>

#ifndef REGISTER_H
#define REGISTER_H

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
    return value >> amount;
    ORR = 12,
    MOV
};

void process_func(int8_t i_flag, enum Operators opcode, int8_t s_flag, enum Register_Names rn, enum Register_Names rd, int16_t operand2);

#endif