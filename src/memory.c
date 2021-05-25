#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//#include <math.h>
#include "memory.h"

#define MEMORY_SIZE 65536
#define BYTE_SIZE 256

static int8_t *memory = NULL;

static int powe(int a, int b) {
    int result = 1;
    while (b > 0)
    {
        b--;
        result *=a;
    }
    return result;
}

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

int32_t get_memory(uint16_t address, int num_bytes)
{
    assert(memory != NULL && num_bytes <= 4 && num_bytes >= 1);
    uint32_t toReturn = 0;
    for (int i = 0; i < num_bytes; i++)
    {
        toReturn += memory[address + i] * powe(BYTE_SIZE, i);
    }

    return toReturn;
}

void free_memory(void)
{
    free(memory);
}