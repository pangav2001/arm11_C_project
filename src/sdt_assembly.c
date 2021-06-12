#include "sdt_assembly.h"
#include "data_processing.h"
#include <assert.h>

#define COND 14 // binary 1110 (i.e instruction always happens)
#define ASCII_0 48

#define ADDRESS instructions->opcodes[1]

// address - maybe char*
uint32_t sdt_assembly(tokens_t *instructions, int current_address, int *next_available_address)
{

    /*
    I = 0 -> Offset is immediate offset
    I = 1 -> Offset is shifted register

    P = 0 -> Post_indexing (offset is add/sub to base reg after transfer)
    P = 1 -> Pre_indexing (offset is add/sub to base reg before transfer)

    U = 0 -> Offset added to base
    U = 1 -> Offset subtracted from base

    L = 0 -> Load
    L = 1 -> Store

    Rn: base register

    Rd: source/destination register

    Offset: either 12 bit immediate value or a register (possibly shifted)
    */

    if (ADDRESS[0] == '=')
    {
        assert(instructions->mnemonic == LDR);

        uint16_t expression;
        STR_TO_INT(ADDRESS, expression);

        //If the expression is less than 0xFF call mov rd, #expression
        if (expression <= 0xFF)
        {
            instructions->mnemonic = MOV;
            ADDRESS[0] = '#';
            return data_process(instructions);
        }

        
    }

    uint32_t result = 0;
    enum Register_Names rd = convert_register(instructions->opcodes[0]);
    enum Register_Names rn = 0;

    //Set bits 31 - 28 to Cond
    result = COND;

    //Set bits 27 - 26 to 01
    result <<= 2;
    result |= 1;

    //Set bit 25 to the I flag
    result <<= 1;
    //TODO

    //Set bit 24 to the P flag
    result <<= 1;
    //TODO

    //Set bit 23 to the U flag
    result <<= 1;
    //TODO

    //Set bits 22 - 21 to 0
    result <<= 2;

    //Set bit 20 to the L flag
    result <<= 1;
    result |= instructions->mnemonic == LDR;

    //Set bits 19 - 16 to the Rn register
    result <<= 4;
    result |= rn;

    //Set bits 15 - 12 to the Rd register
    result <<= 4;
    result |= rd;
}
