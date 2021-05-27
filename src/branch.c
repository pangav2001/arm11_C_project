#include <stdlib.h>
#include "branch.h"
#include "registers.h"
#include <assert.h>
#include <stdio.h>


void branch(int offset){
    // This offset is shifted left 2 bits, sign extended
    //to 32 bits and then added to the PC

    //assert(offset != NULL); want to assert 24 bits in length
    int32_t temp = (int32_t) offset << 2;
   
    // PC is 8 bytes ahead of the instruction that is being executed
    int32_t pc_value = get_reg(PC);
    pc_value  = (pc_value - 8) + temp;
    store_reg(PC, pc_value);
}
