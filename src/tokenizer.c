#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "emulate_src/registers.h"

#define MAX_LINE_LENGTH 511
#define MAX_MNEMONIC_LENGTH 6 //Based on what we need to implement


//returns 0 if not label
//returns length of label otherwise
int16_t is_label(char *line) {
    char *temp = line; //give same pointer
    for (int i = 0; i < MAX_LINE_LENGTH && *temp; i++, temp++) { //*temp should check we are not at /0
        if (*temp == ':') {
            return i;
        }
    }
    return 0;
}


int16_t assign_label_address(char *line, int16_t address)
{
    int16_t length = is_label(line);
    if (length) {
        char *label = malloc(length + 1);
        strncpy(label, line, length);
        //TODO
        //Add the label to hashmap
        //and correct address
        free(label);
        return address; //label so address hasn't changed
    }
    return address + 4; //return next address
}

struct tokens tokenize_instruction(char *line) {
    extract_mnemonic(&line);
    
    struct tokens tokens;
    char *instruction = strdup(line); //Had issues with line not being modifiable before, maybe remove after testing with actual buffer
    char *token;
    char *rest = instruction;

    while(token = strtok_r(rest, ",", &rest)) {
        printf("%s\n", token);
    }

    free(instruction);
    return tokens;

}

//extracts the mnemonic and updates the pointer to after the first " ";
void extract_mnemonic(char** line) {
    char mnemonic[MAX_MNEMONIC_LENGTH];
    for (int i = 0; (*line)[0] != ' '; (*line)++, i++) {
        mnemonic[i] = (*line)[0];
    }
    (*line)++; //remove the leading " "
    printf("%s\n", mnemonic);
    //find a way of turning this char* into the enum
}

enum Register_Names convert_register(char* reg) {
    reg++; //removes leading r
    return strtol(reg, NULL, 10);
}