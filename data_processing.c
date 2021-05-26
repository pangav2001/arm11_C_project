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
        check_c_flag(VALUE_SIZE - amount)
        return value << amount;
    case LSR:
        check_c_flag(amount - 1)
        return (uint32_t)value >> amount;
    case ASR:
        check_c_flag(amount - 1)
        return value >> amount;
    case ROR:
        amount %= 32;
        int32_t right = extract_bits(value, 0, amount - 1);
        int32_t left = extract_bits(value, amount, VALUE_SIZE) - 1;
        check_c_flag(amount - 1)
        return left + (right << (VALUE_SIZE - amount));
    }
}

void process_func(int8_t i_flag, enum Operators opcode, int8_t s_flag, enum Register_Names rn, enum Register_Names rd, int16_t operand2)
{
    int result = 0;
    set_flag_value(Z, result == 0);
    set_flag_value(N, exctract_bits(result, 31, 31));
}
