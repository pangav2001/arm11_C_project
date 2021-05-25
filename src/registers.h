#include <stdint.h>

#ifndef REGISTER_H
#define REGISTER_H

enum Register_Names
{
    R0,
    R1,
    R2,
    R3,
    R5,
    R6,
    R7,
    R8,
    R9,
    R10,
    R11,
    R12,
    SP,
    LR,
    PC,
    CPSR
};

int32_t get_reg(enum Register_Names reg_name);

int store_reg(enum Register_Names reg_name, int32_t data);

void initialize_registers(void);

void free_registers(void);

void print_register_state(void);

#endif