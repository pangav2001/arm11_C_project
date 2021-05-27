#include <stdlib.h>
#include "branch.h"
#include "registers.h"
#include <assert.h>
#include <stdio.h>


void branch(int offset){
    // This offset is shifted left 2 bits, sign extended
    //to 32 bits and then added to the PC

    //assert(offset != NULL); want to assert 24 bits in length
    printf("offset input: %d \n", offset);
    int32_t temp = (int32_t) offset << 2;
   

    // error with negative offset

    // check if offset is negative offset

    int first;
    first = temp;

    while (first >= 10)
    {
        first = first / 10;
    }

    if(first == 1){
        temp = - temp;
    }

    printf("offset %d \n", temp);
    // PC is 8 bytes ahead of the instruction that is being executed
    int32_t pc_value = get_reg(PC);
    printf("pc before %d \n", pc_value);
    pc_value  = (pc_value - 8) + temp;
    printf("pc after %d \n", pc_value);
    store_reg(PC, pc_value);
}
