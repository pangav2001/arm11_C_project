#include <stdint.h>
#include "multiply.h"
#include "registers.h"
#include "flags.h"


void multiply(int A, int S,
 Register_Names Rd ,Register_Names Rn, Register_Names Rs, Register_Names Rm){

    int32_t result = get_reg(Rm) * get_reg(Rs);

    if(A == 1){
        result = result + get_reg(Rn);
    }

    store_reg(Rd,result);

    if(S == 1){
        if(result == 0){
            set_flag(Z);
        }

        
        // N flag is set to last bit of result -- define get last bit func

        int first;
        first = result;

        while(first >= 10){
            first = first / 10;
        }
        if(first == 1){
            set_flag(N);
        }
        
    }

 }


