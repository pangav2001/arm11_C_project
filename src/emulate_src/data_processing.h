#ifndef DATA_PROCESSING
#define DATA_PROCESSING

#include "registers.h"
#include "memory.h"
#include "flags.h"
#include "decode.h"
#include "../tokenizer.h"
#include <stdint.h>


enum Shift_Types
{
    LSL,
    LSR,
    ASR,
    ROR
};

void process_func(int8_t i_flag, enum Mnemonic opcode, int8_t s_flag, enum Register_Names rn, enum Register_Names rd, int16_t operand2);

int32_t immediate_operand(int16_t operand2, int8_t i_flag, int8_t s_flag);

#endif
