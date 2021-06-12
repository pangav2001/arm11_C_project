#include "sdt_assembly.h"
#include "data_processing.h"
#include "tokenizer.h"
#include "assemble.h"
#include "emulate_src/decode.h"
#include <assert.h>

#define COND 14 // binary 1110 (i.e instruction always happens)
#define ASCII_0 48
#define UINT11_MAX 2047

#define ADDRESS instructions->opcodes[1]

// address - maybe char*
uint32_t sdt_assembly(tokens_t *instructions, uint32_t current_address, uint32_t *next_available_address, uint32_t *assembled_program)
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

        save_instruction(assembled_program, next_available_address, expression);
        
        uint32_t offset = *next_available_address - current_address;

        *next_available_address += 4;

        //CHANGE R15 TO PC
        sprintf(instructions->opcodes[1], "[R15, %u]", offset);

        return sdt_assembly(instructions, current_address, next_available_address, assembled_program);
    }

    uint32_t result = 0;
    enum Register_Names rd = convert_register(instructions->opcodes[0]);

    int num_bracket_opcodes = 0;
    //Remove the last ']' from <expression>
    instructions->opcodes[1][strlen(instructions->opcodes[1]) - 1] = '\0';

    //Tokenize the opcodes within []
    char **bracket_opcodes = extract_opcodes(instructions->opcodes[1] + 1, &num_bracket_opcodes);
    assert(num_bracket_opcodes);

    //Set the base register Rn
    enum Register_Names rn = convert_register(bracket_opcodes[0]);

    uint16_t offset = 0;

    //Check for pre/post index
    if (instructions->num_opcode == 2)
    {
        //Pre-Index

        //Set bit 24(P) to 1
        SET_BITS(24, 1);

        if (num_bracket_opcodes > 1)
        {
            if (bracket_opcodes[1][0] == '#')
            {
                STR_TO_INT(bracket_opcodes[1], offset);
            }
            else
            {
                //Set bit 25(I) to 1
                SET_BITS(25, 1);

                //TODO optional
            }
        }
    }
    else
    {
        if (instructions->opcodes[2][0] == '#')
        {
            STR_TO_INT(bracket_opcodes[2], offset);
        }
        else
        {
            //Set bit 25(I) to 1
            SET_BITS(25, 1);
            //TODO optional
        }
    }

    //Set bits 31 - 28 to Cond
    SET_BITS(28, COND);

    //Set bits 27 - 26 to 01
    SET_BITS(26, 1);

    //Set bit 25 to the I flag
    //TODO

    //Set bit 23 to the U flag
    SET_BITS(23, 1); //TEMP

    //Set bits 22 - 21 to 0

    //Set bit 20 to the L flag
    SET_BITS(20, instructions->mnemonic == LDR);

    //Set bits 19 - 16 to the Rn register
    SET_BITS(16, rn);

    //Set bits 15 - 12 to the Rd register
    SET_BITS(12, rd);

    //Set bits 11 - 0 to offset
    assert(offset <= UINT11_MAX);
    SET_BITS(0, offset);

    return result;
}
