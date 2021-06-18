#include <stdio.h>
#include "headers/flags.h"
#include "headers/registers.h"
#include "headers/decode.h"

int check_cond(enum Condition_Code condition_code)
{
    switch (condition_code)
    {
    case EQ:
        return get_flag(Z) == 1;
    case NE:
        return get_flag(Z) == 0;
    case GE:
        return get_flag(N) == get_flag(V);
    case LT:
        return get_flag(N) != get_flag(V);
    case GT:
        return get_flag(Z) == 0 && (get_flag(N) == get_flag(V));
    case LE:
        return get_flag(Z) == 1 || (get_flag(N) != get_flag(V));
    case AL:
        return 1;
    default:
        return 0;
    }
}

void set_flag(enum Flag flag)
{
    switch (flag)
    {
    case N:
        store_reg(CPSR, (INT32_MIN) | get_reg(CPSR));
        break;
    case Z:
        store_reg(CPSR, (1 << 30) | get_reg(CPSR));
        break;
    case C:
        store_reg(CPSR, (1 << 29) | get_reg(CPSR));
        break;
    case V:
        store_reg(CPSR, (1 << 28) | get_reg(CPSR));
        break;
    }
}

void reset_flag(enum Flag flag)
{
    switch (flag)
    {
    case N:
        store_reg(CPSR, (7 << 28) & get_reg(CPSR)); //0111
        break;
    case Z:
        store_reg(CPSR, ((11 << 28)) & get_reg(CPSR)); //1011
        break;
    case C:
        store_reg(CPSR, ((13 << 28)) & get_reg(CPSR)); //1101
        break;
    case V:
        store_reg(CPSR, ((14 << 28)) & get_reg(CPSR)); //1110
        break;
    }
}

int get_flag(enum Flag flag)
{
    uint32_t cpsr = get_reg(CPSR);
    return extract_bits(cpsr, 31 - flag, 31 - flag);
}

void set_flag_value(enum Flag flag, int8_t value, int8_t s_flag)
{
    if (s_flag)
    {
        value ? set_flag(flag) : reset_flag(flag);
    }
}