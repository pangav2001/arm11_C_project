#include "multiply.h"
#include <stdarg.h>

#define COND 0xE
#define _1001 0x9

uint32_t multiply(enum Mnemonic instruction, char *rd_string, char *rm_string, char *rs_string, ...)
{
    enum Register_Names rd = strtol(rd_string, NULL, 10);
    enum Register_Names rm = strtol(rm_string, NULL, 10);
    enum Register_Names rs = strtol(rs_string, NULL, 10);
    enum Register_Names rn = 0;
    if(instruction == MLA)
    {
        va_list ap;
        char *rn_string;
        va_start(ap, rn_string);
        rn = strtol(rn_string, NULL, 10);
        va_end(ap);
    }

    //Set bits 31 - 28 to Cond
    uint32_t result = COND;

    //Set bits 27 - 22 to 0
    result <<= 6;

    //Set bit 21(A)
    result <<= 1;
    result |= instruction == MLA;

    //Set bit 20(S) to 0
    result <<= 1;

    //Set bits 19 - 16 to Rd
    result <<= 4;
    result |= rd;

    //Set bits 15 - 12 to Rn
    result <<= 4;
    result |= rn;

    //Set bits 11 - 8 to Rs
    result <<= 4;
    result |= rs;

    //Set bits 7 - 4 to 1001
    result <<= 4;
    result |= _1001;

    //Set bits 3 - 0 to Rm
    result <<= 4;
    result |= rm;

    return result;
}
