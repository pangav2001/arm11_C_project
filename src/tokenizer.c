#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

//returns 0 if not label
//returns length of label otherwise
int16_t is_label(char *line)
{
    char *temp = line; //give same pointer
    for (int i = 0; i < MAX_LINE_LENGTH && *temp; i++, temp++)
    { //*temp should check we are not at /0
        if (*temp == ':')
        {
            return i;
        }
    }
    return 0;
}

int16_t assign_label_address(char *line, int16_t address)
{
    int16_t length = is_label(line);
    if (length)
    {
        char *label = malloc(length + 1);
        strncpy(label, line, length);
        label[length] = '\0';
        //TODO
        //Add the label to hashmap
        //and correct address
        printf("%s\n", label);
        free(label);
        return address; //label so address hasn't changed
    }
    return address + 4; //return next address
}

tokens* tokenize_instruction(char *line)
{
    tokens *tokens = calloc(1,sizeof(tokens));

    enum Mnemonic mnemonic = extract_mnemonic(&line);

    char *instruction = strdup(line); //Had issues with line not being modifiable before, maybe remove after testing with actual buffer
    char *token;
    char *rest = instruction;
    char **opcodes = calloc(MAX_OPCODE, sizeof(char *)); //remember to free this in assemble!
    int i;
    for (i = 0; (token = strtok_r(rest, ",", &rest)); i++)
    {
        //printf("%s\n", token);
        char *curr = calloc(1, strlen(token));
        strcpy(curr, token);
        opcodes[i] = curr;
    }
    tokens->mnemonic = mnemonic;
    tokens->num_opcode = i;
    tokens->opcodes = opcodes;

    free(instruction);
    return tokens;
}

//extracts the mnemonic and updates the pointer to after the first " ";
enum Mnemonic extract_mnemonic(char **line)
{
    char mnemonic[MAX_MNEMONIC_LENGTH];
    int i;
    for (i = 0; (*line)[0] != ' '; (*line)++, i++)
    {
        mnemonic[i] = (*line)[0];
    }
    mnemonic[i] = '\0'; //ensure it's terminated
    (*line)++; //remove the leading " "
    return convert_mnemonic(mnemonic);
}

enum Register_Names convert_register(char *reg)
{
    reg++; //removes leading r
    return strtol(reg, NULL, 10);
}

enum Mnemonic convert_mnemonic(char *mnemonic)
{
    for (int i = 0; mnemonic_mapping[i].mnemonic; i++)
    {
        if (strcmp(mnemonic, mnemonic_mapping[i].str) == 0)
        {
            return mnemonic_mapping[i].mnemonic;
        }
    }
    perror("Bad Mnemonic");
    return -1;
}

void free_tokens(tokens* tokens) {
    for (int i = 0; i < tokens->num_opcode; i++) {
        free(tokens->opcodes[i]);
    }
    free(tokens->opcodes);
    free(tokens);
}