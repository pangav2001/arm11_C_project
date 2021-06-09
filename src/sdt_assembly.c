#include "sdt_assembly.h"

#define COND 0xE // binary 1110 (i.e instruction always happens)

// address - maybe char*
uint32_t sdt_assembly(enum Mnemonic instruction, enum Register_Names rd, char* address,
int* current_address, int* next_available_address){

    // bits 31-28 to cond
    uint32_t result = COND;

    //bit 27 - 26 = 01
    result = result | (1 << 26);
    result = result & ~(1 << 27);


    // bit 15 - 12 has Rd_number -- figure this part out

  
    uint32_t expression;

    // checking for numeric constant case
    bool numeric_constant = false;
    if(address[0] == '='){
        numeric_constant = true;
        expression = strtol(address+3,NULL,16);
    }

    
    enum Register_Names Rn = NULL; 
    bool pre_index = false;

    // check if pre/post index if not numeric constant
    if(!numeric_constant){

        // determine register 
        char* rn_pos;
        rn_pos = strstr(address,"r");
        rn_pos++;   //since register int is after r
        Rn = *rn_pos;

        char* hashtag_pos;
        hashtag_pos = strstr(address,"#");
    
        if(hashtag_pos){
            // to distinguish between [Rn,<#expression>] && [Rn],<#expression>
            char* closing_bracket;
            closing_bracket = strstr(address,"]");
            
            if(hashtag_pos < closing_bracket){
                pre_index = true;
                *closing_bracket = '\0'; //maybe unnecessary but to clearly indicate where number should stop
            }else{
                pre_index = false;
            }

            expression = strtol(hashtag_pos++,NULL,10);

        }else{
            pre_index = true; // only pre_index has no #
            expression = 0;
        }
    }


    switch(instruction){
        case LDR:
        //Set L = 1 (bit 19)
        result = (result >> 19) | 1;

        //address in form <=expression>
        if(numeric_constant){
            // if address is just a numeric constant - then pre indexed
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


    if(pre_index){
        // set the pre-index bit (bit 24)
        result = (result >> 24) | 1; 
    }else{
        // zero the pre-index bit (bit 24)
        result = (result >> 24) & 0; 
    }

    // bit 

}
