#include <stdlib.h>
#include "headers/branch.h"
#include "headers/registers.h"
#include <assert.h>
#include <stdio.h>


void branch(int32_t offset){
    // This offset is shifted left 2 bits, sign extended
    //to 32 bits and then added to the PC

    int32_t temp = offset << 2;
    
    // PC is 8 bytes ahead of the instruction that is being executed
    int32_t pc_value = get_reg(PC);
    pc_value  = (pc_value + 4) + temp; //PC is 12 ahead, we always subtract 8 so we need + 4 to compensate for PC +8
    store_reg(PC, pc_value);
}
