#include "multiply.h"

#define COND 14
#define _1001 9

// mul, Rd, Rm, Rs
// mla Rd, Rm, Rs, Rn

uint32_t multiply(tokens *instructions)
{
    assert(instructions->num_opcode > 2);

    enum Register_Names rd = convert_register(instructions->opcodes[0]);
    enum Register_Names rm = convert_register(instructions->opcodes[1]);
    enum Register_Names rs = convert_register(instructions->opcodes[2]);
    enum Register_Names rn = 0;
    if(instructions->mnemonic == MLA)
    {
        assert(instructions->num_opcode == 4);
        rn = convert_register(instructions->opcodes[3]);
    }

    //Set bits 31 - 28 to Cond
    uint32_t result = COND;

    //Set bits 27 - 22 to 0
    result <<= 6;

    //Set bit 21(A)
    result <<= 1;
    result |= instructions->mnemonic == MLA;

    //Set bit 20(S) to 0
    result <<= 1;

    //Set bits 19 - 16 to Rd
    result <<= 4;
    result |= rd;

    //Set bits 15 - 12 to Rn
    result <<= 4;
    result |= rn;

    //Set bits 11 - 8 to Rs
    result <<= 4;
    result |= rs;

    //Set bits 7 - 4 to 1001
    result <<= 4;
    result |= _1001;

    //Set bits 3 - 0 to Rm
    result <<= 4;
    result |= rm;

    return result;
}
