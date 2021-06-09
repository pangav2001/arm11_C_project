#ifndef BRANCH_ASS
#define BRANCH_ASS

#include "tokenizer.h"
#include <stdint.h>

uint32_t branch(enum Mnemonic instruction, char* expression, int16_t current_address);

#endif