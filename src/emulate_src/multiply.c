#include <stdint.h>
#include "multiply.h"
#include "registers.h"
#include "flags.h"
#include <assert.h>


extern void set_flag_value(enum Flag flag, int8_t value, int8_t s_flag);             

void multiply(int a_flag, int s_flag,
              enum Register_Names rd, enum Register_Names rn, enum Register_Names rs, enum Register_Names rm)
{

    assert(rd != rm);

    int32_t result = get_reg(rm) * get_reg(rs);

    if (a_flag)
    {
        result = result + get_reg(rn);
    }

    store_reg(rd, result);
    set_flag_value(Z, result == 0, s_flag);

    // N flag is set to bit 31 of result

    int first;
    first = result;
    while (first >= 10)
    {
        first = first / 10;
    }
    set_flag_value(N, first == 1, s_flag);
}
