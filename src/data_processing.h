#ifndef DP_ASS
#define DP_ASS

#include "tokenizer.h"
#include "emulate_src/registers.h"
#include <stdint.h>



// <and, eor, sub, rsb, add, orr>, Rd, Rn, Operand2
// <mov>, Rd, Operand2
// <tst, teq, cmp> Rn, Operand2
uint32_t data_process(tokens_t *instructions);

#define STR_TO_INT(S, I)                 \
    do                                   \
    {                                    \
        if (S[1] == '0' && S[2] == 'x')  \
        {                                \
            I = strtol(S + 3, NULL, 16); \
        }                                \
        else                             \
        {                                \
            I = strtol(S + 1, NULL, 10); \
        }                                \
    } while (0)


#define SET_BITS(LSB, VAL) result |= (VAL) << (LSB)

#endif