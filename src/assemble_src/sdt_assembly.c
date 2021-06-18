#include "headers/sdt_assembly.h"
#include "headers/data_processing.h"
#include "headers/tokenizer.h"
#include "headers/assemble.h"
#include "../emulate_src/headers/decode.h"
#include <assert.h>

#define COND 14 // binary 1110 (i.e instruction always happens)
#define UINT12_MAX 4095
#define ARM_PIPELINE_OFFSET 8

#define ADDRESS instructions->operands[1]

inline static uint16_t calculate_offset(char **expression, uint32_t *result, uint8_t num_operand)
{

    if (expression[0][0] == '#')
    {
        if (expression[0][1] == '-' || expression[0][1] == '+')
        {
            //Set bit 23(U) to 1 if the number is positive
            SET_BITS(*result, 23, expression[0][1] == '+');

            return string_to_int(expression[0] + 2);
        }

        //Set bit 23(U) to 1 since number is positive
        SET_BITS(*result, 23, 1);

        return string_to_int(expression[0] + 1);
    }

    //Set bit 23(U) to 1 since number is positive
    SET_BITS(*result, 23, 1);

    //Set bit 25(I) to 1
    SET_BITS(*result, 25, 1);

    enum Register_Names rm = convert_register(expression[0]);
    uint8_t shift = 0;
    uint16_t offset = 0;

    if (num_operand > 2)
    {
        shift = calculate_register_shift(expression[1]);
    }

    //Set bits 11 - 4 to shift
    SET_BITS(offset, 4, shift);

    //Set bits 3 - 0 to the Rm register
    SET_BITS(offset, 0, rm);

    return offset;

    //TODO optional
}

uint32_t sdt_assembly(tokens_t *instructions, uint16_t current_address, uint16_t *next_available_address, uint32_t *assembled_program)
{
    if (ADDRESS[0] == '=')
    {
        assert(instructions->mnemonic == LDR);

        uint32_t expression;
        expression = string_to_int(ADDRESS + 1);

        //If the expression is less than 0xFF call mov rd, #expression
        if (expression <= 0xFF)
        {
            instructions->mnemonic = MOV;
            ADDRESS[0] = '#';
            return data_process(instructions);
        }

        save_instruction(assembled_program, *next_available_address, expression);

        uint16_t offset = *next_available_address - current_address - ARM_PIPELINE_OFFSET;

        *next_available_address += 4;

        sprintf(instructions->operands[1], "[PC, #%u]", offset);

        return sdt_assembly(instructions, current_address, next_available_address, assembled_program);
    }

    uint32_t result = 0;
    enum Register_Names rd = convert_register(instructions->operands[0]);

    int num_bracket_opcodes = 0;
    //Remove the last ']' from <expression>
    instructions->operands[1][strlen(instructions->operands[1]) - 1] = '\0';

    //Tokenize the opcodes within []
    char **bracket_opcodes = extract_operands(instructions->operands[1] + 1, &num_bracket_opcodes);
    assert(num_bracket_opcodes);

    //Set the base register Rn
    enum Register_Names rn = convert_register(bracket_opcodes[0]);

    uint16_t offset = 0;

    //Check for pre/post index
    if (instructions->num_operand == 2)
    {
        //Pre-Index

        //Set bit 24(P) to 1
        SET_BITS(result, 24, 1);

        //Check if the instruction is in the from Mnemonic Register [Register]
        if (num_bracket_opcodes > 1)
        {
            offset = calculate_offset(bracket_opcodes + 1, &result, num_bracket_opcodes);
        }
        else
        {
            //Set bit 23(U) to 1 since number is positive
            SET_BITS(result, 23, 1);
        }
    }
    else
    {
        //Post-Index
        offset = calculate_offset(instructions->operands + 2, &result, instructions->num_operand - 1);
    }

    //Set bits 31 - 28 to Cond
    SET_BITS(result, 28, COND);

    //Set bits 27 - 26 to 01
    SET_BITS(result, 26, 1);

    //Set bits 22 - 21 to 0

    //Set bit 20 to the L flag
    SET_BITS(result, 20, instructions->mnemonic == LDR);

    //Set bits 19 - 16 to the Rn register
    SET_BITS(result, 16, rn);

    //Set bits 15 - 12 to the Rd register
    SET_BITS(result, 12, rd);

    //Set bits 11 - 0 to offset
    assert(offset <= UINT12_MAX);
    SET_BITS(result, 0, offset);

    return result;
}
