#include <stdio.h>
#include "single_data_transfer.h"
#include "decode.h"
#include "memory.h"

//From the spec
//If PC is used make sure we +8 or something!!!!

void single_data_transfer(int8_t i, int8_t p, int8_t u, int8_t l, enum Register_Names rn, enum Register_Names rd, uint16_t offset)
{
    int16_t address = calculate_address(rn, offset, u, i, p);
    switch (l)
    {
    case 0:
        //store
    case 1:
        //load
    default:
        printf("L bit is not valid");
        //throw some error
    }
}

int16_t calculate_address(enum Register_Names rn, uint32_t offset, int8_t u, int8_t i, int8_t p)
{
    switch (i)
    {
    case 0:
        switch (p)
        {
        case 0:
            return post_index(rn, offset, u);
        case 1:
            return pre_index(rn, offset, u);
        }
    case 1:
        //cons function
    }
}

int16_t pre_index(enum Register_Names rn, uint32_t offset, int8_t u)
{
    return add_sub(u, get_reg(rn), offset);
}

int16_t post_index(enum Register_Names rn, uint32_t offset, int8_t u)
{
    int32_t rn_data = get_reg(rn);
    store_reg(rn, add_sub(u, rn_data, offset));
    return rn_data;
}

void load(enum Register_Names rd, int16_t address)
{
    store_reg(rd, get_memory(address, 4));
}

void store(enum Register_Names rd, int16_t address)
{
    //wait for pan
}

//0 mean sub 1 mean add
int32_t add_sub(int8_t sign, int32_t a, int32_t b)
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