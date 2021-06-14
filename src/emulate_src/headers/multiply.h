#ifndef _mULTIPLY_H_EMULATOR_
#define _mULTIPLY_H_EMULATOR_

#include <stdint.h>
#include "registers.h"

void multiply(int A, int S,
              enum Register_Names Rd, enum Register_Names Rn, enum Register_Names Rs, enum Register_Names Rm);

#endif