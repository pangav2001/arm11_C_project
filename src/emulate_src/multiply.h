#ifndef MULTIPLY_H
#define MULTIPLY_H

#include <stdint.h>
#include "registers.h"

void multiply(int A, int S,
              enum Register_Names Rd, enum Register_Names Rn, enum Register_Names Rs, enum Register_Names Rm);

#endif