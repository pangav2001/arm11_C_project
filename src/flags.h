
#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>

enum Condition_Code
{
    EQ,
    NE,
    GE = 10,
    LT,
    GT,
    LE,
    AL
};

enum Flag {
    N,
    Z,
    C,
    V
};

#define SET_FLAG_VALUE(F, V)             \
    if (s_flag)                          \
    {                                    \
        V ? set_flag(F) : reset_flag(F); \
    }

int check_cond(enum Condition_Code condition_code);

void set_flag(enum Flag flag);

void reset_flag(enum Flag flag);

int get_flag(enum Flag);

#endif
