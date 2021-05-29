#include <stdint.h>
#include "multiply.h"
#include "registers.h"
#include "flags.h"
#include <assert.h>

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
    SET_FLAG_VALUE(Z, result == 0)

    // N flag is set to bit 31 of result -- define get last bit func

    int first;
    first = result;
    while (first >= 10)
    {
        first = first / 10;
    }
    SET_FLAG_VALUE(N, first == 1)
}
