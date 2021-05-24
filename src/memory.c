#include "memory.h"

extern int8_t *memory;

#define MEM_SIZE 65536;

// load function
uint32_t load(uint16_t address, int num_bytes)
{
    assert(num_bytes <= 4);
    assert(num_bytes >= 1);
    uint32_t toReturn;
    for (int i = 0; i < num_bytes; i++)
    {
        toReturn = *memory + 8 * i;
    }

    return toReturn;
}
