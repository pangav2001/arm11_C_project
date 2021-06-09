#include "data_processing.h"
#include <stdarg.h>
#include <string.h>

#define COND 14

uint32_t data_process(enum Mnemonic instruction, ...)
{
    va_list ap;
    enum Register_Names rd = 0;
    enum Register_Names rn = 0;
    enum Register_Names rm = 0;
    enum Mnemonic shift;
    char *operand2;
    uint8_t immediate_value;

    va_start(ap, instruction);
    switch (instruction)
    {
    case AND: case EOR: case SUB: case RSB: case ADD: case ORR:
        char *str = va_arg(ap, char *);
        rd = strtol(str, NULL, 10);
        str = va_arg(ap, char *);
        rn = strtol(str, NULL, 10);
        str = va_arg(ap, char *);
        strcpy(operand2, str);
        break;
    case MOV:
        char *str = va_arg(ap, char *);
        rd = strtol(str, NULL, 10);
        str = va_arg(ap, char *);
        strcpy(operand2, str);
        break;
    case TST: TEQ: CMP:
        char *str = va_arg(ap, char *);
        rn = strtol(str, NULL, 10);
        str = va_arg(ap, char *);
        strcpy(operand2, str);
        break;
    default:
        perror("Unsupported instruction");
        break;
    }

    if (operand2[0] == '#')
    {
        if (operand2[1] == '0' && operand2[2] == 'x')
        {
            //Skip "#0x" and convert to hex number
            immediate_value = strtol(operand2 + 3, NULL, 16);
        }
        else
        {
            //Skip "#" and convert to decimal number
            immediate_value = strtol(operand2 + 1, NULL, 10);
        }
    } else {
        
    }

    va_end(ap);


    //Set bits 31 - 28 to Cond
    uint32_t result = COND;

    //Set bits 27 - 25 to 0
    result <<= 2;
}