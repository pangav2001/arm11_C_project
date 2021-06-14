#ifndef _BRANCH_H_ASSEMBLER_
#define _BRANCH_H_ASSEMBLER_

#include "tokenizer.h"
#include <stdint.h>
#include "hash_table.h"

uint32_t branch_assembly(tokens_t *instructions, int16_t current_address, Hash_Table *table);

#endif