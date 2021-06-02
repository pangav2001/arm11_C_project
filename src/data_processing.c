#include "data_processing.h"

#define VALUE_SIZE 32

#define ROTATE_BITS extract_bits(operand2, 8, 11)
#define IMMEDIATE_VALUE (uint8_t) extract_bits(operand2, 0, 7)

#define RM extract_bits(operand2, 0, 3)
#define SHIFT_BY_REGISTER extract_bits(operand2, 4, 4)
#define REG_SHIFT_TYPE extract_bits(operand2, 5, 6)

#define RS_LAST_BYTE get_reg(extract_bits(operand2, 8, 11))
#define SHIFT_CONSTANT (uint8_t) extract_bits(operand2, 7, 11)

enum Arithmetic_Operations
{
    SUBTRACTION,
    ADDITION
};

enum Shift_Types
{
    LSL,
    LSR,
    ASR,
    ROR
};

extern void set_flag_value(enum Flag flag, int8_t value, int8_t s_flag);

static inline void check_c_flag_logical(int8_t bit, int32_t value, int32_t amount, int8_t s_flag)
{
    if (amount >= VALUE_SIZE)
    {
        set_flag_value(C, 0, s_flag);
    }
    else
    {
        set_flag_value(C, extract_bits(value, bit, bit), s_flag);
    }
}

static int32_t shift(enum Shift_Types shift_type, int32_t value, int32_t amount, int8_t s_flag)
{
    if (amount == 0)
    {
        set_flag_value(C, 0, s_flag);
        return value;
    }

    switch (shift_type)
    {
    case LSL:
        check_c_flag_logical(VALUE_SIZE - amount, value, amount, s_flag);
        return value << amount;
    case LSR:
        check_c_flag_logical(amount - 1, value, amount, s_flag);
        return (uint32_t)value >> amount;
    case ASR:
        check_c_flag_logical(amount - 1, value, amount, s_flag);
        return value >> amount;
    case ROR:
        amount %= 32;
        int32_t right = extract_bits(value, 0, amount - 1);
        int32_t left = extract_bits(value, amount, VALUE_SIZE - 1);
        check_c_flag_logical(amount - 1, value, amount, s_flag);
        return left + (right << (VALUE_SIZE - amount));
    default:
        return 0;
    }
}

int32_t immediate_operand(int16_t operand2, int8_t i_flag, int8_t s_flag)
{
    if (i_flag)
    {
        return shift(ROR, IMMEDIATE_VALUE, 2 * ROTATE_BITS, s_flag);
    }

    else if (SHIFT_BY_REGISTER)
    {
        return shift(REG_SHIFT_TYPE, get_reg(RM), RS_LAST_BYTE, s_flag);
    }
    else
    {
        return shift(REG_SHIFT_TYPE, get_reg(RM), SHIFT_CONSTANT, s_flag);
    }
}

static void overflow_check_arithmetic(int32_t a, int32_t b, int32_t result, int8_t s_flag, enum Arithmetic_Operations op)
{
    int overflow = (result < 0) | (result > INT32_MAX);
    if (overflow)
    {
        set_flag_value(C, op, s_flag);
    }
    else
    {
        set_flag_value(C, !op, s_flag);
    }
}

void process_func(int8_t i_flag, enum Operators opcode, int8_t s_flag, enum Register_Names rn, enum Register_Names rd, int16_t operand2)
{
    int32_t result = 0;
    int32_t immediate_operand2 = immediate_operand(operand2, i_flag, s_flag);

    switch (opcode)
    {
    case TST:
    case AND:
        result = get_reg(rn) & immediate_operand2;
        break;
    case TEQ:
    case EOR:
        result = get_reg(rn) ^ immediate_operand2;
        break;
    case CMP:
    case SUB:
        result = get_reg(rn) - immediate_operand2;
        overflow_check_arithmetic(get_reg(rn), immediate_operand2, result, s_flag, SUBTRACTION);
        break;
    case RSB:
        result = immediate_operand2 - get_reg(rn);
        overflow_check_arithmetic(get_reg(rn), immediate_operand2, result, s_flag, SUBTRACTION);
        break;
    case ADD:
        result = get_reg(rn) + immediate_operand2;
        overflow_check_arithmetic(get_reg(rn), immediate_operand2, result, s_flag, ADDITION);
        break;
    case ORR:
        result = get_reg(rn) | immediate_operand2;
        break;
    case MOV:
        result = immediate_operand2;
        break;
    }

    set_flag_value(Z, result == 0, s_flag);
    set_flag_value(N, extract_bits(result, 31, 31), s_flag);

    if (!(opcode == TST || opcode == TEQ || opcode == CMP))
    {
        store_reg(rd, result);
    }
}
