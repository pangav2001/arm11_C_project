
#ifndef single_data_transfer_assembly
#define single_data_transfer_assembly

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "../../emulate_src/headers/registers.h"

uint32_t sdt_assembly(tokens_t* instructions, uint16_t current_address, uint16_t *next_available_address, uint32_t *assembled_program);

#endif