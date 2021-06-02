#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "memory.h"

#define LE_LOOP int i = 0; i < num_bytes; i++
#define BE_LOOP int i = num_bytes - 1; i >= 0; i--

#define COMBINE_BITS(EXP)                                 \
    for (EXP)                                             \
    {                                                     \
        toReturn = (toReturn << 8) | memory[address + i]; \
    }

static uint8_t *memory = NULL;

void initialize_memory(void)
{
    if (memory == NULL)
    {
        memory = calloc(MEMORY_SIZE, sizeof(int8_t));
        assert(memory != NULL);
    }
    else
    {
        printf("Memory is already initialized\n");
    }
}

int store_memory(uint16_t address, int8_t data)
{
    assert(memory != NULL);
    memory[address] = data;
    return 0;
}

int32_t get_memory(uint16_t address, int num_bytes, enum Endian endian)
{
    assert(memory != NULL && num_bytes <= 4 && num_bytes >= 1);
    int32_t toReturn = 0;
    if (endian == LITTLE)
    {
        COMBINE_BITS(LE_LOOP)
    }
    else
    {
        COMBINE_BITS(BE_LOOP)
    }

    return toReturn;
}

void free_memory(void)
{
    free(memory);
}