#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "registers.h"

#define NUM_REG 17
// #define BYTE_REG 4

// static int8_t **registers = NULL;


// void initialize(void)
// {
//     if (registers != NULL)
//     {
//         registers = (int8_t **)calloc(NUM_REG, sizeof(int8_t *));

//         assert(registers != NULL);

//         registers[0] = (int8_t *)calloc(NUM_REG * BYTE_REG, sizeof(int8_t));

//         if (!registers[0])
//         {
//             free(registers);
//             printf("Throw some error *****");
//             return; //throw some error or something
//         }

//         for (int i = 1; i < NUM_REG; i++)
//         {
//             registers[i] = registers[i - 1] + BYTE_REG;
//         }
//     }
//     else
//     {
//         printf("Registers are already initialized");
//     }
// }

static int32_t *registers = NULL;

void initialize(void) {
    if (registers != NULL)
    {
        registers = calloc(NUM_REG, sizeof(int32_t));
        assert(registers != NULL);
    }
    else
    {
        printf("Registers are already initialized");
    }
}

int32_t get_reg(enum Register_Names reg_name)
{
    return registers[reg_name];
}

int store_reg(enum Register_Names reg_name, int32_t data)
{
    registers[reg_name] = data;
    return 0;
}
