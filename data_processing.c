#include "data_processing.h"

#define set_flag_value(F, V) V ? set_flag(F) : reset_flag(F)

#define VALUE_SIZE 32

#define check_c_flag(L)                               \
    if (amount > VALUE_SIZE - 1 && value != 0)        \
    {                                                 \
        set_flag(C);                                  \
    }                                                 \
    else                                              \
    {                                                 \
        set_flag_value(C, extract_bits(value, L, L)); \
    }

#define ROTATE_BITS extract_bits(operand2, 8, 11)
#define IMMEDIATE_VALUE extract_bits(operand2, 0, 7)

#define RM exctract_bits(operand2, 0, 3)
#define SHIFT_BY_REGISTER extract_bits(operand2, 4, 4)
#define REG_SHIFT_TYPE exctract_bits(operand2, 5, 6)

#define RS_LAST_BYTE exctract_bits(operand2, 7, 0)
#define SHIFT_CONSTANT exctract_bits(operand2, 7, 11)

static enum Shift_Types {
    LSL,
    LSR,
    ASR,
    ROR
};

static int32_t shift(enum Shift_Types shift_type, int32_t value, int32_t amount)
{
    switch (shift_type)
    {
    case LSL:
        check_c_flag(VALUE_SIZE - amount) return value << amount;
    case LSR:
        check_c_flag(amount - 1) return (uint32_t)value >> amount;
    case ASR:
        check_c_flag(amount - 1) return value >> amount;
    case ROR:
        amount *= 2;
        amount %= 32;
        int32_t right = extract_bits(value, 0, amount - 1);
        int32_t left = extract_bits(value, amount, VALUE_SIZE) - 1;
        check_c_flag(amount - 1) return left + (right << (VALUE_SIZE - amount));
    }
}

int32_t immediate_operand(int16_t operand2, int8_t i_flag)
{
    if (i_flag)
    {
        shift(ROR, ROTATE_BITS, IMMEDIATE_VALUE);
    }
    else if (SHIFT_BY_REGISTER)
    {
        int32_t rs = get_reg(extract_bits(operand2, 8, 11));
        return shift(REG_SHIFT_TYPE, get_reg(RM), RS_LAST_BYTE);
    }
    else
    {
        return shift(REG_SHIFT_TYPE, get_reg(RM), SHIFT_CONSTANT);
    }
}

void process_func(int8_t i_flag, enum Operators opcode, int8_t s_flag, enum Register_Names rn, enum Register_Names rd, int16_t operand2)
{
    int result = 0;
    set_flag_value(Z, result == 0);
    set_flag_value(N, exctract_bits(result, 31, 31));
}
