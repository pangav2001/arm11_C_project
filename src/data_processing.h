#include "registers.h"
#include "memory.h"
#include <stdint.h>

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

void process_func(int i_flag, enum Operators opcode, enum Register_Names rn, enum Register_Names rd, int16_t operand2);