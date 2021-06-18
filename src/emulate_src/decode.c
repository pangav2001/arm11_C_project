#include "headers/decode.h"

//variables named with 'o' represent a one
//and 'z' represent a zero

struct data_processing
{
    unsigned cond : 4;
    unsigned decide : 2;
    unsigned i_bit : 1;
    unsigned opcode : 4;
    unsigned s_bit : 1;
    unsigned rn : 4;
    unsigned rd : 4;
    unsigned operand_2 : 12;
};

struct multiply
{
    unsigned cond : 4;
    unsigned zzzzzz : 6;
    unsigned a_bit : 1;
    unsigned s_bit : 1;
    unsigned rd : 4;
    unsigned rn : 4;
    unsigned rs : 4;
    unsigned ozzo : 4;
    unsigned rm : 4;
};

struct sdt
{
    unsigned cond : 4;
    unsigned decide : 2;
    unsigned i_bit : 1;
    unsigned p_bit : 1;
    unsigned u_bit : 1;
    unsigned zz : 2;
    unsigned l_bit : 1;
    unsigned rn : 4;
    unsigned rd : 4;
    unsigned offset : 12;
};

struct branch
{
    unsigned cond : 4;
    unsigned ozoz : 4;
    signed offset : 24;
};

int32_t extract_bits(int32_t data, unsigned int start, unsigned int end)
{
    assert(start <= end);
    unsigned int mask = 0;
    for (unsigned i = start; i <= end; i++)
    {
        mask |= 1 << i;
    }

    return (mask & data) >> start;
}

void decode(int32_t instruction)
{
    int decide = extract_bits(instruction, 26, 27);
    int cond = extract_bits(instruction, 28, 31);
    if (check_cond(cond))
    {
        switch (decide)
        {
        case 0:
        {
            int8_t isMul1 = extract_bits(instruction, 22, 25);
            int8_t isMul2 = extract_bits(instruction, 4, 7);
            if (!(isMul1 == 0 && isMul2 == 9))
            {
                struct data_processing *instr;
                instr = calloc(1, sizeof(struct data_processing));
                assert(instr);

                instr->cond = cond;
                instr->i_bit = extract_bits(instruction, 25, 25);
                instr->opcode = extract_bits(instruction, 21, 24);
                instr->s_bit = extract_bits(instruction, 20, 20);
                instr->rn = extract_bits(instruction, 16, 19);
                instr->rd = extract_bits(instruction, 12, 15);
                instr->operand_2 = extract_bits(instruction, 0, 11);
                process_func(instr->i_bit, instr->opcode, instr->s_bit, instr->rn, instr->rd, instr->operand_2);
                free(instr);
            }
            else
            {
                struct multiply *instr;
                instr = calloc(1, sizeof(struct multiply));
                assert(instr);

                instr->cond = cond;
                instr->zzzzzz = 0;
                instr->a_bit = extract_bits(instruction, 21, 21);
                instr->s_bit = extract_bits(instruction, 20, 20);
                instr->rd = extract_bits(instruction, 16, 19);
                instr->rn = extract_bits(instruction, 12, 15);
                instr->rs = extract_bits(instruction, 8, 11);
                instr->ozzo = isMul2;
                instr->rm = extract_bits(instruction, 0, 3);
                multiply(instr->a_bit, instr->s_bit, instr->rd, instr->rn, instr->rs, instr->rm);
                free(instr);
            }
        }
        break;

        case 1:
        {
            struct sdt *instr;
            instr = calloc(1, sizeof(struct sdt));
            assert(instr);

            instr->cond = cond;
            instr->decide = decide;
            instr->i_bit = extract_bits(instruction, 25, 25);
            instr->p_bit = extract_bits(instruction, 24, 24);
            instr->u_bit = extract_bits(instruction, 23, 23);
            instr->zz = 0;
            instr->l_bit = extract_bits(instruction, 20, 20);
            instr->rn = extract_bits(instruction, 16, 19);
            instr->rd = extract_bits(instruction, 12, 15);
            instr->offset = extract_bits(instruction, 0, 11);
            single_data_transfer(instr->i_bit, instr->p_bit, instr->u_bit, instr->l_bit, instr->rn, instr->rd, instr->offset);
            free(instr);
        }
        break;

        case 2:
        {
            struct branch *instr;
            instr = calloc(1, sizeof(struct branch));
            assert(instr);
            
            instr->cond = cond;
            instr->ozoz = 10;
            instr->offset = extract_bits(instruction, 0, 23);
            branch(instr->offset);
        }
        break;

        default:
            break;
        }
    }
}
