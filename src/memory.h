#include <stdint.h>

#ifndef MEMORY_H
#define MEMORY_H

extern int8_t *memory;

int store(uint16_t address, int8_t data);

uint32_t load(uint16_t address, int num_bytes);

#endif