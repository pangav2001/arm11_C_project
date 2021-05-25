#include <stdint.h>

enum Condition_Codes
{
    EQ,
    NE,
    GE,
    LT,
    GT,
    LE,
    AL
};

enum Flags {
    N,
    Z,
    C,
    V
};

int check_cond(enum Condition_Code);

void set_flag(enum Flags flag);

void reset_flag(enum Flags flag);
