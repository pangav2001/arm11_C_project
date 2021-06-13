#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEMORY_SIZE 65536
#define BYTE_SIZE 256

enum Endian {
    LITTLE,
    BIG
};

void initialize_memory(void);

int store_memory(uint16_t address, int8_t data);

int32_t get_memory(uint16_t address, int num_bytes, enum Endian endian);

void free_memory(void);

#endif