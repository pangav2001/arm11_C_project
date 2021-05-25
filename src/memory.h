#include <stdint.h>

#ifndef MEMORY_H
#define MEMORY_H

void initialize_memory(void);

int store_memory(uint16_t address, int8_t data);

int32_t get_memory(uint16_t address, int num_bytes);

void free_memory(void);

#endif