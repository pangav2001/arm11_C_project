#include <stdio.h>
#include "headers/single_data_transfer.h"
#include "headers/decode.h"
#include "headers/memory.h"
#include "headers/data_processing.h"

#define MAX_ADDRESS 65536

static void load(enum Register_Names rd, uint16_t address);
static void store(enum Register_Names rd, uint16_t address);
static int32_t add_sub(int8_t sign, int32_t a, int32_t b);

void single_data_transfer(int8_t i, int8_t p, int8_t u, int8_t l, enum Register_Names rn, enum Register_Names rd, uint16_t offset)
{

    int32_t rn_data = get_reg(rn);
    rn_data = (rn == PC) ? rn_data - 4 : rn_data; //accomodate for pipeline

    //32 bits so that a wrap-around (overflow)
    //on the 16 bit offset can be detected
    /*
    Why? Because theoritically uint16_t can hold
    any possible address, but if the result of 
    immediate_operand is > MAX_ADDRESS, then the
    result will wrap around to fit in 16 bits.
    Hence, our check for `address > MAX_ADDRESS`
    will fail despite address being larger
    */
    uint32_t new_offset = offset;

    //if the offset is not immediate, then get the new offset
    if (i)
    {
        new_offset = immediate_operand(offset, 0, 0);
    }

    uint32_t address = add_sub(u, rn_data, new_offset);

    if (address == 0x20200000)
    {
        printf("One GPIO pin from 0 to 9 has been accessed\n");
    }
    else if (address == 0x20200004)
    {
        printf("One GPIO pin from 10 to 19 has been accessed\n");
    }
    else if (address == 0x20200008)
    {
        printf("One GPIO pin from 20 to 29 has been accessed\n"); 
    }
    else if (address == 0x2020001C)
    {
        printf("PIN ON\n");
    }
    else if (address == 0x20200028)
    {
        printf("PIN OFF\n");
    }
    else if (address > MAX_ADDRESS)
    {
        printf("Error: Out of bounds memory access at address 0x%08x\n", address);
    }
    else
    {
        //in both store and load, if p = 0 (post-indexing) we want to use the
        //the contents of the base register as the address for our operation
        //and THEN replace it with the new address
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
        }
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
        perror("Unsupported sign");
        exit(1);
    }
}

static void load(enum Register_Names rd, uint16_t address)
{
    store_reg(rd, get_memory(address, 4, BIG));
}

static void store(enum Register_Names rd, uint16_t address)
{
    int32_t rd_data = get_reg(rd);
    for (int i = 0; i < 4; i++)
    {
        store_memory(address + i, extract_bits(rd_data, i * 8, (i * 8) + 7));
    }
}