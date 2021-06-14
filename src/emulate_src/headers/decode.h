#ifndef _DECODE_H_EMULATOR_
#define _DECODE_H_EMULATOR_

#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include "memory.h"
#include "data_processing.h"
#include "multiply.h"
#include "single_data_transfer.h"
#include "flags.h"
#include "branch.h"

int32_t extract_bits(int32_t data, unsigned int start, unsigned int end);

void decode(int32_t instruction);

#endif
