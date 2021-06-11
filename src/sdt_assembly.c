#include "sdt_assembly.h"

#define COND 0xE // binary 1110 (i.e instruction always happens)
#define ASCII_0 48

// address - maybe char*
uint32_t sdt_assembly(enum Mnemonic instruction, enum Register_Names rd, char* address,
int* current_address, int* next_available_address){

    // bits 31-28 to cond
    uint32_t result = COND;
    result <<= 28;

    //bit 27 - 26 = 01
    result = result | (1 << 26);
    result = result & ~(1 << 27);

    //I is always 0 in not optional instructions
    result = result | (1 << 25);

    // bit 22 - 21 = 00 -- redundant

    //always add offset - U will be 1 (DOUBLE CHECK this!)
    result = result & ~(1 << 23);

    // bit 15 - 12 has Rd_number
    result |= rd << 12;
  
    uint32_t expression;

    // checking for numeric constant case
    bool numeric_constant = false;
    if(address[0] == '='){
        numeric_constant = true;
        expression = strtol(address+3,NULL,16); // convert hex to int
    }

    
    enum Register_Names Rn = NULL; 
    bool pre_index = false;

    // check if pre/post index if not numeric constant
    if(!numeric_constant){

        // determine register 
        char* rn_pos;
        rn_pos = strstr(address,"r");
        rn_pos++;   //since register int is after r
        Rn =(int) *rn_pos - ASCII_0; // since *rn_pos returns ascii value

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
            
            expression = strtol(hashtag_pos++,NULL,10); //DOUBLE CHECK

        }else{
            // only pre_index has no #
            pre_index = true; 
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
                char str_expression[5];
                char input[] = "#";
                strcpy(str_expression,address++);
                strcat(input, str_expression);
                return data_process(MOV,rd,input);

            }else{
            // expression at end of assembled program
            *next_available_address = expression;
            int offset =  next_available_address - (current_address - 8); // -8 due to pipeline being two instructions behind
            char newAddress[100] = "[";
            char PC_str[] = get_reg(PC);
            char offset_str[] = offset;
            char closing_bracket[] = "]";
            strcat(newAddress,PC_str);
            strcat(newAddress,offset_str);
            strcat(newAddress,closing_bracket);

            return sdt_assembly(LDR,rd,newAddress,current_address++,next_available_address++);
            }
        }
        break;

        case STR:
        //Set L = 0 (bit 19)
        result = result & ~(1 << 19);
        break;
    }


    if(pre_index){
        // set the pre-index bit (bit 24)
        result = (result >> 24) | 1; 
    }else{
        // zero the pre-index bit (bit 24)
        result = (result >> 24) & 0; 
    }

    // set Rn to rn
    result |= Rn << 16; 
    //set offset to expression
    result |= expression << 0;   

}
