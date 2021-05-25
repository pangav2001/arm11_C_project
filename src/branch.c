#include <stdlib.h>
#include "branch.h"
#include "registers.h"
#include <assert.h>


void branch(int offset){
    // This offset is shifted left 2 bits, sign extended
    //to 32 bits and then added to the PC

    int temp = offset << 2;
    //temp = 
    // PC is 8 bytes ahead of the instruction that is being executed
}