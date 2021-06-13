#include "headers/branch.h"
#include <assert.h>
#include "headers/data_processing.h"

#define EXPRESSION instructions->opcodes[0]

#define ARM_OFFSET 8


uint32_t branch_assembly(tokens_t *instructions, int16_t current_address, Hash_Table *table)
{
    uint32_t result = 0;
    assert(instructions->mnemonic >= BEQ && instructions->mnemonic <= B);

    //Set bits 31 - 28 to Cond
    SET_BITS(result, 28, instructions->mnemonic - BRANCH_INDEX);


    //Set bits 27 - 25 to 101 and 24 to 0
    SET_BITS(result, 24, B_1010);

    //Calculate offset
    int16_t target_address = 0;

    //Calculate the target address
    assert((target_address = table_search(table, EXPRESSION)) != -1);

    int32_t offset = target_address - current_address - ARM_OFFSET;
    offset >>= 2;
    offset &= (1<<24) - 1;

    //Set bits 23 - 0 to offset
    SET_BITS(result, 0, offset);

    return result;
}
