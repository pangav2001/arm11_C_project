#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "memory.h"

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


int32_t get_memorye(uint16_t address, int num_bytes)
{
    assert(memory != NULL && num_bytes <= 4 && num_bytes >= 1);
    int32_t toReturn = 0;
    for (int i = 0; i < num_bytes; i++)
    {
        toReturn |= ((uint32_t) memory[address + i] & 0xFF) << (i*8);
    }

    return toReturn;
}

int32_t get_memory(uint16_t address, int num_bytes)
{
    assert(memory != NULL && num_bytes <= 4 && num_bytes >= 1);
    int32_t toReturn = 0;
    for (int i = 0; i < num_bytes; i++)
    {
        toReturn += (memory[address + i] << (i*8));
    }

    return toReturn % ((int32_t) pow(2, 32));
}

//Sorry?
int32_t read_memory(uint16_t address, int num_bytes)
{
    uint8_t temp[4];
    assert(memory != NULL && num_bytes <= 4 && num_bytes >= 1);

    for (int i = 0; i < num_bytes; i++)
    {
        temp[i] = memory[address + i];
    }

    memory[address] = temp[3];
    memory[address + 1] = temp[2];
    memory[address + 2] = temp[1];
    memory[address + 3] = temp[0];

    return get_memory(address, num_bytes);
}

void free_memory(void)
{
    free(memory);
}