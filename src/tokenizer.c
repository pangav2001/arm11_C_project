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

int16_t assign_label_address(char *line, int16_t address, Hash_Table *table)
{
    int16_t length = is_label(line);
    if (length)
    {
        char *label = malloc(length + 1);
        strncpy(label, line, length);
        label[length] = '\0';

        //I can just do this right even if same key?
        table_insert(table, label, address);

        free(label);
        return address; //label so address hasn't changed
    }
    return address + 4; //return next address
}

tokens_t *tokenize_instruction(char *line)
{
    tokens_t *tokens = calloc(1, sizeof(tokens_t));

    enum Mnemonic mnemonic = extract_mnemonic(&line);

    int num_opcodes;
    tokens->opcodes = extract_opcodes(line, &num_opcodes);
    tokens->num_opcode = num_opcodes;
    tokens->mnemonic = mnemonic;
    return tokens;
}

char** extract_opcodes(char* line, int *num_opcodes) {
    char *instruction = strdup(line); //Had issues with line not being modifiable before, maybe remove after testing with actual buffer
    char *token;
    char *rest = instruction;
    char **opcodes = calloc(MAX_OPCODE, sizeof(char *));
    int i;
    for (i = 0; (token = strtok_r(rest, ",", &rest)); i++)
    {
        //printf("%s\n", token);
        char *curr = calloc(1, strlen(token));
        strcpy(curr, token);
        remove_whitespace(curr);
        opcodes[i] = curr;
    }
    *num_opcodes = i;
    free(instruction);
    return opcodes;
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
    (*line)++;          //remove the leading " "
    return convert_mnemonic(mnemonic);
}

enum Register_Names convert_register(char *reg)
{
    reg++; //removes leading r
    return strtol(reg, NULL, 10);
}

Enum_Map mnemonic_mapping[] = {
    {"and", AND},
    {"eor", EOR},
    {"sub", SUB},
    {"rsb", RSB},
    {"add", ADD},
    {"tst", TST},
    {"teq", TEQ},
    {"cmp", CMP},
    {"orr", ORR},
    {"mov", MOV},
    {"mul", MUL},
    {"mla", MLA},
    {"ldr", LDR},
    {"str", STR},
    {"beq", BEQ},
    {"bne", BNE},
    {"bge", BGE},
    {"blt", BLT},
    {"bgt", BGT},
    {"ble", BLE},
    {"b", B},
    {"lsl", LSL_M},
    {"andeq", ANDEQ},
    {"", -1} //for iterating
};

enum Mnemonic convert_mnemonic(char *mnemonic)
{
    for (int i = 0; mnemonic_mapping[i].mnemonic != -1; i++)
    {
        if (strcmp(mnemonic, mnemonic_mapping[i].str) == 0)
        {
            return mnemonic_mapping[i].mnemonic;
        }
    }
    perror("Bad Mnemonic");
    return -1;
}

void free_opcode(char **opcodes, int num_opcode) {
    for (int i = 0; i < num_opcode; i++)
    {
        free(opcodes[i]);
    }
    free(opcodes);
}

void free_tokens(tokens_t *tokens)
{
    free_opcode(tokens->opcodes, tokens->num_opcode);
    free(tokens);
}

void remove_whitespace(char* text) {
    char* copy = strdup(text);
    //Remove from start
    for(int i = 0; text[i] == ' '; i++) {
            copy++;
    }
    //remove from end
    int i;
    for (i = 0; copy[i] && copy[i] != ' '; i++);
    copy[i] = '\0';
    strcpy(text, copy);
}