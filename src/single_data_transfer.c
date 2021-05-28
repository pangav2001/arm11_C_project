#include <stdio.h>
#include "single_data_transfer.h"
#include "decode.h"
#include "memory.h"
#include "data_processing.h"

static uint16_t calculate_address(enum Register_Names rn, uint16_t offset, int8_t u, int8_t i, int8_t p);
static void load(enum Register_Names rd, uint16_t address);
static void store(enum Register_Names rd, uint16_t address);

void single_data_transfer(int8_t i, int8_t p, int8_t u, int8_t l, enum Register_Names rn, enum Register_Names rd, uint16_t offset)
{
    rn = (rn == PC) ? rn - 8 : rn; //accomodate for pipeline
    uint16_t address = calculate_address(rn, offset, u, i, p);
    switch (l)
    {
    case 0:
        store(rd, address);
        break;
    case 1:
        //printf("here: rd: %d address %d\n", rd, address);
        load(rd, address);
        break;
    default:
        printf("L bit is not valid\n");
        break;
        //throw some error
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
    store_reg(rd, get_memory(address, 4));
}

static void store(enum Register_Names rd, uint16_t address)
{
    int32_t rd_data = get_reg(rd);
    for (int i = 0; i < 4; i++)
    {
        store_memory(address + i, extract_bits(rd_data, i * 8, (i * 8) + 7));
    }
}

static int16_t pre_index(enum Register_Names rn, uint16_t offset, int8_t u)
{
    return add_sub(u, get_reg(rn), offset);
}

static int16_t post_index(enum Register_Names rn, uint16_t offset, int8_t u)
{
    int32_t rn_data = get_reg(rn);
    store_reg(rn, add_sub(u, rn_data, offset));
    return rn_data;
}

static uint16_t calculate_address(enum Register_Names rn, uint16_t offset, int8_t u, int8_t i, int8_t p)
{
    switch (i)
    {
    case 0:
        //printf("%d\n", p);
        switch (p)
        {
        case 0:
            return post_index(rn, offset, u);
        case 1:
            return pre_index(rn, offset, u);
        default:
            break;
        }
    case 1:
        //connys function maybe work maybe not
        return immediate_operand(offset, 0, 0);
    default:
        return 0;
        break;
    }
}