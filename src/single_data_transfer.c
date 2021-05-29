#include <stdio.h>
#include "single_data_transfer.h"
#include "decode.h"
#include "memory.h"
#include "data_processing.h"

#define MAX_ADDRESS 65536

static void load(enum Register_Names rd, uint16_t address);
static void store(enum Register_Names rd, uint16_t address);
static int32_t add_sub(int8_t sign, int32_t a, int32_t b);

void single_data_transfer(int8_t i, int8_t p, int8_t u, int8_t l, enum Register_Names rn, enum Register_Names rd, uint16_t offset)
{

    int32_t rn_data = get_reg(rn);
    rn_data = (rn == PC) ? rn_data - 4 : rn_data; //accomodate for pipeline
    uint16_t new_offset = offset;
    if (i)
    {
        new_offset = immediate_operand(offset, 0, 0);
    }
    uint32_t address = add_sub(u, rn_data, new_offset);
    //printf("Rn: %d Rn_data: %d address: 0x%08x\n", rn, rn_data, address);
    if (address > MAX_ADDRESS)
    {
        printf("Error: Out of bounds memory access at address 0x%08x\n", address);
    }
    else
    {
        switch (l)
        {
        case 0:
            if (!p)
            {
                store(rd, rn_data);
            }
            else
            {
                store(rd, address);
            }
            break;
        case 1:
            //printf("here: rd: %d address %d\n", rd, address);
            if (!p)
            {
                load(rd, rn_data);
            }
            else
            {
                load(rd, address);
            }
            break;
        default:
            printf("L bit is not valid\n");
            break;
            //throw some error
        }
        //rn_data = get_reg(rn);
        if (!p)
        {
            store_reg(rn, address);
        }
    }
}

static int32_t add_sub(int8_t sign, int32_t a, int32_t b)
{
    switch (sign)
    {
    case (0):
        return a - b;
    case (1):
        return a + b;
    default:
        return -1; //throw an error
    }
}

static void load(enum Register_Names rd, uint16_t address)
{
    store_reg(rd, get_memory(address, 4, BIG));
}

static void store(enum Register_Names rd, uint16_t address)
{
    int32_t rd_data = get_reg(rd);
    //printf("Rd: %d Rd data: 0x%08x Write to 0x%08x:\n", rd, rd_data, address);
    for (int i = 0; i < 4; i++)
    {
        store_memory(address + i, extract_bits(rd_data, i * 8, (i * 8) + 7));
    }
}