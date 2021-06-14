#ifndef _SINGLE_DATA_TRANSFER_H_EMULATOR_
#define _SINGLE_DATA_TRANSFER_H_EMULATOR_

#include <stdint.h>
#include "registers.h"

void single_data_transfer(int8_t i, int8_t p, int8_t u, int8_t l, enum Register_Names rn, enum Register_Names rd, uint16_t offset);

#endif