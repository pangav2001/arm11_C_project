#include <stdint.h>

#ifndef REGISTER_H
#define REGISTER_H

enum registerNames {R0,
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
CPSR};

int32_t get_reg(int reg_name);

int store_reg(int reg_name, int32_t data);

// mov

#endif