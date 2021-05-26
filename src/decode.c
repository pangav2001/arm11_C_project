#include "memory.h"

int32_t extract_bits(int32_t data, unsigned int start, unsigned int end)
{
    unsigned int r = 0;
    for (unsigned i = start; i <= end; i++)
    {
        r |= 1 << i;
    }

    return (r & data) >> start;
}