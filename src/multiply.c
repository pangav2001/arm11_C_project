#include <stdint.h>
#include "multiply.h"
#include "registers.h"
#include "flags.h"
#include <assert.h>

void multiply(int A, int S,
              enum Register_Names Rd, enum Register_Names Rn, enum Register_Names Rs, enum Register_Names Rm)
{


    assert(Rd != Rm);

    int32_t result = get_reg(Rm) * get_reg(Rs);

    if (A == 1)
    {
        result = result + get_reg(Rn);
    }

    store_reg(Rd, result);

    if (S == 1)
    {
        if (result == 0)
        {
            set_flag(Z);
        }else{
            reset_flag(Z);
        }

        // N flag is set to bit 31 of result -- define get last bit func

        int first;
        first = result;

        while (first >= 10)
        {
            first = first / 10;
        }
        if (first == 1)
        {
            set_flag(N);
        }else{
            reset_flag(N);
        }
    }
}
