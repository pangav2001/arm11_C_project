#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "headers/registers.h"

#define NUM_REG 17

static int32_t *registers = NULL;

void initialize_registers(void) {
    if (registers == NULL)
    {
        registers = calloc(NUM_REG, sizeof(int32_t));
        assert(registers);
    }
    else
    {
        printf("Registers are already initialized\n");
    }
}

int32_t get_reg(enum Register_Names reg_name)
{
    assert(registers != NULL);
    return registers[reg_name];
}

int store_reg(enum Register_Names reg_name, int32_t data)
{
    assert(registers != NULL);
    registers[reg_name] = data;
    return 0;
}

void free_registers(void) {
    free(registers);
}
