#include "data_processing.h"
#include "emulate_src/data_processing.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define COND 14
#define UINT4_MAX 15
#define UINT5_MAX 31

#define OPERAND2(I) instructions->opcodes[operand2_start + I]

enum Shift_Types convert_shift_types(char *str)
{
    char *shift_types[4] = {
        "lsl",
        "lsr",
        "asr",
        "ror"};

    for (enum Shift_Types i = LSL; i <= ROR; i++)
    {
        if (strcmp(shift_types[i], str) == 0)
        {
            return i;
        }
    }

    perror("Unsupported shift type");
    exit(1);
}

uint8_t calculate_register_shift(char *epxression)
{
    uint8_t shift = 0;
    //Change magic numbers
    char *shift_type_string = malloc(5 * sizeof(char));
    char *rs_string = malloc(5 * sizeof(char));

    sscanf(epxression, "%s %s", shift_type_string, rs_string);
    enum Shift_Types shift_type = convert_shift_types(shift_type_string);
    free(shift_type_string);

    if (rs_string[0] == '#')
    {
        //Set bits 11 - 7 (7 - 3 of shift) to the immediate value
        uint8_t immediate_val = string_to_int(rs_string + 1);
        assert(immediate_val <= UINT5_MAX);
        SET_BITS(shift, 3, immediate_val);
    }
    else
    {
        //Set bits 11 - 8 (7 - 4 of shift) to the Rs register
        enum Register_Names rs = convert_register(rs_string);

        assert(rs >= R0 && rs <= CPSR);
        SET_BITS(shift, 4, rs);
    }

    //Set bits 6 - 5 (2 - 1 of shift) to the shift type
    SET_BITS(shift, 1, shift_type);

    //Set bit 4 (0 of shift) to the shift type flag
    SET_BITS(shift, 0, rs_string[0] != '#');

    free(rs_string);

    return shift;
}

uint32_t data_process(tokens_t *instructions)
{
    enum Register_Names rd = 0;
    enum Register_Names rn = 0;
    enum Register_Names rm = 0;
    uint8_t operand2_start;

    switch (instructions->mnemonic)
    {
    case AND:
    case EOR:
    case SUB:
    case RSB:
    case ADD:
    case ORR:
        assert(instructions->num_opcode >= 3);
        rd = convert_register(instructions->opcodes[0]);
        rn = convert_register(instructions->opcodes[1]);
        operand2_start = 2;
        break;
    case MOV:
        assert(instructions->num_opcode >= 2);
        rd = convert_register(instructions->opcodes[0]);
        operand2_start = 1;
        break;
    case TST:
    case TEQ:
    case CMP:
        assert(instructions->num_opcode >= 2);
        rn = convert_register(instructions->opcodes[0]);
        operand2_start = 1;
        break;
    default:
        perror("Unsupported instruction");
        exit(1);
        break;
    }

    //Check that the registers were read correctly
    assert(rd >= R0 && rd <= CPSR);
    assert(rn >= R0 && rn <= CPSR);

    uint32_t result = 0;

    //Set bits 31 - 28 to Cond
    SET_BITS(result, 28, COND);

    //Set bits 27 - 26 to 0

    //Set bit 25 to the I flag
    SET_BITS(result, 25, OPERAND2(0)[0] == '#');

    //Set bits 24 - 21 to the opcode
    SET_BITS(result, 21, instructions->mnemonic - DATA_PROCESSING_INDEX);

    //Set bit 20 to the S flag
    SET_BITS(result, 20, instructions->mnemonic >= TST && instructions->mnemonic <= CMP);

    //Set bits 19 - 16 to the Rn register
    SET_BITS(result, 16, rn);

    //Set bits 15-12 to the Rd register
    SET_BITS(result, 12, rd);

    //Set bits 11 - 0 to operand2

    if (OPERAND2(0)[0] == '#')
    {
        uint32_t immediate_result;
        uint8_t rotate = 0;

        immediate_result = string_to_int(OPERAND2(0) + 1);

        int right_shifts = 0;
        if (immediate_result > UINT8_MAX)
        {
            while (immediate_result % 4 == 0)
            {
                right_shifts += 2;
                immediate_result >>= 2;
            }

            rotate = (32 - right_shifts) / 2;
        }

        assert(immediate_result <= UINT8_MAX);
        assert(rotate <= UINT4_MAX);

        //Set the right rotation to zero and immediate value to the result
        SET_BITS(result, 8, rotate);
        SET_BITS(result, 0, immediate_result);
    }
    else
    {
        rm = convert_register(OPERAND2(0));
        uint8_t shift = 0;
        if (instructions->num_opcode > operand2_start + 1)
        {
            shift = calculate_register_shift(OPERAND2(1));
        }

        //Set bits 11 - 4 to shift
        SET_BITS(result, 4, shift);

        //Set bits 3 - 0 to the Rm register
        SET_BITS(result, 0, rm);
    }

    return result;
}