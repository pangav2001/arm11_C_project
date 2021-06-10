#ifndef BRANCH_ASS
#define BRANCH_ASS

#include "tokenizer.h"
#include <stdint.h>
#include "hash_table.h"

uint32_t branch_assembly(tokens *instructions, int16_t current_address, Hash_Table *table);

#endif