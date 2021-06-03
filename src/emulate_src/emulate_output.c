#include <stdio.h>
#include <stdint.h>
#include "emulate_output.h"

void print_registers(void)
{
    printf("Registers:\n");
    for (enum Register_Names i = R0; i <= R12; i++)
    {
        int32_t val = get_reg(i);
        printf("$%-2d : %10d (0x%08x)\n", i, val, val);
    }
    int32_t val = get_reg(PC);
    printf("PC  : %10d (0x%08x)\n", val, val);
    val = get_reg(CPSR);
    printf("CPSR: %10d (0x%08x)\n", val, val);
}

void print_memory(void)
{
    printf("Non-zero memory:\n");
    int32_t mem;
    for (int i = 0; i < MEMORY_SIZE; i+=4)
    {   
        //try to think of a way such that we won't 
        //iterate through the whole memory block
        mem = get_memory(i, 4, LITTLE);
        if(mem != 0)
            {
                printf("0x%08x: 0x%08x\n", i, mem);
            }
    }
}