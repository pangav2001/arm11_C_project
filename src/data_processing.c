#include "data_processing.h"

#define VALUE_SIZE 32

#define ROTATE_BITS extract_bits(operand2, 8, 11)
#define IMMEDIATE_VALUE (uint32_t) extract_bits(operand2, 0, 7)

#define RM extract_bits(operand2, 0, 3)
#define SHIFT_BY_REGISTER extract_bits(operand2, 4, 4)
#define REG_SHIFT_TYPE extract_bits(operand2, 5, 6)

#define RS_LAST_BYTE extract_bits(operand2, 7, 0)
#define SHIFT_CONSTANT (uint8_t) extract_bits(operand2, 7, 11)

static enum Shift_Types { LSL,
                          LSR,
                          ASR,
                          ROR
};

static inline void check_c_flag_logical(int8_t bit, int32_t value, int32_t amount, int8_t s_flag)
{
    if (amount >= VALUE_SIZE)
    {
        SET_FLAG_VALUE(C, 0);
    }
    else
    {
        SET_FLAG_VALUE(C, extract_bits(value, bit, bit));
    }
}

static int32_t shift(enum Shift_Types shift_type, int32_t value, int32_t amount, int8_t s_flag)
{
    //Late night stuff
    if (amount == 0) {
        return value;
    } 
    //
    switch (shift_type)
    {
    case LSL:
        check_c_flag_logical(VALUE_SIZE - amount, value, amount, s_flag);
        return value << amount;
    case LSR:
        check_c_flag_logical(amount - 1, value, amount, s_flag);
        return (uint32_t) value >> amount;
    case ASR:
        check_c_flag_logical(amount - 1, value, amount, s_flag);
        return value >> amount;
    case ROR:
        amount %= 32;
        int32_t right = extract_bits(value, 0, amount - 1);
        int32_t left = extract_bits(value, amount, VALUE_SIZE - 1);
        check_c_flag_logical(amount - 1, value, amount, s_flag);
        return left + (right << (VALUE_SIZE - amount));
    }
}

int32_t immediate_operand(int16_t operand2, int8_t i_flag, int8_t s_flag)
{
    //printf("%d\n", operand2);
    if (i_flag)
    {
        //printf("%d\n", ROTATE_BITS);
        return shift(ROR, IMMEDIATE_VALUE, 2 * ROTATE_BITS, s_flag);
    }
    else if (SHIFT_BY_REGISTER)
    {
        int32_t rs = get_reg(extract_bits(operand2, 8, 11));
        return shift(REG_SHIFT_TYPE, get_reg(RM), RS_LAST_BYTE, s_flag);
    }
    else
    {
        return shift(REG_SHIFT_TYPE, get_reg(RM), SHIFT_CONSTANT, s_flag);
    }
}

static void overflow_check_addition(int32_t a, int32_t b, int32_t result, int8_t s_flag)
{
    if (a > 0 && b > 0 && result < 0 || a < 0 && b < 0 && result > 0)
    {
        SET_FLAG_VALUE(C, 1);
    }
    else
    {
        SET_FLAG_VALUE(C, 0);
    }
}

void process_func(int8_t i_flag, enum Operators opcode, int8_t s_flag, enum Register_Names rn, enum Register_Names rd, int16_t operand2)
{
    int32_t result = 0;
    int32_t immediate_operand2 = immediate_operand(operand2, i_flag, s_flag);

    printf("DATA PROCESSINGS WAS CALLED\n");

    switch (opcode)
    {
    case AND:
        result = get_reg(rn) & immediate_operand2;
        break;
    case EOR:
        result = get_reg(rn) ^ immediate_operand2;
        break;
    case SUB:
        result = get_reg(rn) - immediate_operand2;
        overflow_check_addition(get_reg(rn), -immediate_operand2, result, s_flag);
        break;
    case RSB:
        result = immediate_operand2 - get_reg(rn);
        overflow_check_addition(get_reg(rn), -immediate_operand2, result, s_flag);
        break;
    case ADD:
        result = get_reg(rn) + immediate_operand2;
        overflow_check_addition(get_reg(rn), immediate_operand2, result, s_flag);
        break;
    case TST:
        result = get_reg(rn) & immediate_operand2;
        break;
    case TEQ:
        result = get_reg(rn) ^ immediate_operand2;
        break;
    case CMP:
        result = get_reg(rn) - immediate_operand2;
        overflow_check_addition(get_reg(rn), -immediate_operand2, result, s_flag);
        // if(get_flag(C))
        // {
        //     SET_FLAG_VALUE(C, 0);
        // }
        // else
        // {
        //     SET_FLAG_VALUE(C, 1);
        // }
        break;
    case ORR:
        result = get_reg(rn) | immediate_operand2;
        break;
    case MOV:
        result = immediate_operand2;
        break;
    }
    
    SET_FLAG_VALUE(Z, result == 0);
    SET_FLAG_VALUE(N, extract_bits(result, 31, 31));

    if(!(opcode == TST || opcode == TEQ || opcode == CMP))
    {
        store_reg(rd, result);
    }
}
