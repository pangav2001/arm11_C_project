#include "headers/multiply.h"
#include "headers/data_processing.h"
#include <assert.h>

#define COND 14
#define B_1001 9

uint32_t assemble_multiply(tokens_t *instructions)
{
    assert(instructions->num_operand > 2);

    enum Register_Names rd = convert_register(instructions->operands[0]);
    enum Register_Names rm = convert_register(instructions->operands[1]);
    enum Register_Names rs = convert_register(instructions->operands[2]);
    enum Register_Names rn = 0;
    if (instructions->mnemonic == MLA)
    {
        assert(instructions->num_operand == 4);
        rn = convert_register(instructions->operands[3]);
    }

    uint32_t result = 0;

    //Set bits 31 - 28 to Cond
    SET_BITS(result, 28, COND);

    //Set bits 27 - 22 to 0

    //Set bit 21(A)
    SET_BITS(result, 21, instructions->mnemonic == MLA);

    //Set bit 20(S) to 0

    //Set bits 19 - 16 to Rd
    SET_BITS(result, 16, rd);

    //Set bits 15 - 12 to Rn
    SET_BITS(result, 12, rn);

    //Set bits 11 - 8 to Rs
    SET_BITS(result, 8, rs);

    //Set bits 7 - 4 to 1001
    SET_BITS(result, 4, B_1001);

    //Set bits 3 - 0 to Rm
    SET_BITS(result, 0, rm);

    return result;
}
