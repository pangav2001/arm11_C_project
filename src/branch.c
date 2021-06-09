#include "branch.h"
#include <assert.h>



uint32_t branch(enum Mnemonic instruction, char* expression, int16_t current_address, Hash_Table table)
{
    uint32_t result;

    //Set bits 31 - 28 to Cond
    result = instruction - BRANCH_INDEX;

    //Set bits 27 - 25 to 101 and 24 to 0
    result <<= 4;
    result |= _1010;

    //Calculate offset
    int16_t target_address = 0;
    
    //Calculate the target address
    assert(target_address = search(&table, expression));

    /*****May need to add/subtract 4/8/12 bits*******/
    int32_t offset = target_address - current_address;
    offset >>= 2;

    //Set bits 23 - 0 to offset
    result <<= 24;
    result |= extract_bits(offset, 0, 23);


    return result;
}
