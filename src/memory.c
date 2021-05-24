#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "memory.h"

#define MEMORY_SIZE 65536

static int8_t *memory = NULL;

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

int store(uint16_t address, int8_t data)
{
    memory[address] = data;
    return 0;
}

int32_t load(uint16_t address, int num_bytes)
{
    assert(num_bytes <= 4 && num_bytes >= 1);
    uint32_t toReturn;
    for (int i = 0; i < num_bytes; i++)
    {
        toReturn = *memory + 8 * i;
    }

    return toReturn;
}

void free_memory(void)
{
    free(memory);
}