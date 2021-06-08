#include "sdt_assembly.h"

#define COND 0xE // binary 1110 (i.e instruction always happens)

// address - maybe char*
uint32_t sdt_assembly(enum Mnemonic instruction, enum Register_Names rd, char* address){
    
    // bits 31-28 to cond
    uint32_t result = COND;

    //bit 27 - 26 = 01
    result = (result >> 26) | 1;
    result = (result >> 27) & 0;

    // bit 15 - 12 has Rd_number
    result = (result >> )


    // given post/pre indexing true or false
    bool pre_index = true;

    // value of expression
    uint16_t expression = address;

    // we can determine which case we are in
    // if address starts with = then numeric constant
    bool numeric_constant = false;

    switch(instruction){
        case LDR:
        //Set L = 1 (bit 19)
        result = (result >> 19) | 1;

        //address in form <=expression>
        if(numeric_constant){
            // if address is just an expression/ numeric constant - then pre indexed
            pre_index = true;

            if(expression <= 0xFF){
            // return mov instruction i.e mov r0 #0x42
            }else{
            // expression at end of assembled program
            }
        }
        break;

        case STR:
        //Set L = 0 (bit 19)
        result = (result >> 19) & 0;
        break;
    }

    // deal with Rn
    enum Register_Names Rn; 

    if(pre_index){
        // set the pre-index bit (bit 24)
        result = (result >> 24) | 1; 
    }else{
        // zero the pre-index bit (bit 24)
        result = (result >> 24) & 0; 
    }

    // bit 

}
