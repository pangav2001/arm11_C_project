#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "headers/tokenizer.h"
#include <assert.h>

#define INFINITY 9999

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
        assert(label);

        strncpy(label, line, length);
        label[length] = '\0';

        table_insert(table, label, address);

        free(label);
        return address; //label so address hasn't changed
    }
    return address + 4; //return next address
}

tokens_t *tokenize_instruction(char *line)
{
    tokens_t *tokens = calloc(1, sizeof(tokens_t));
    assert(tokens);

    enum Mnemonic mnemonic = extract_mnemonic(&line);

    int num_operands;
    tokens->operands = extract_operands(line, &num_operands);
    tokens->num_operand = num_operands;
    tokens->mnemonic = mnemonic;
    return tokens;
}

char **extract_operands(char *line, int *num_operands)
{
    char *instruction = strdup(line);
    char *token;
    char *rest = instruction;
    char **operands = calloc(MAX_OPERAND, sizeof(char *));
    assert(operands);

    int i;
    for (i = 0; (token = strtok_r(rest, ",", &rest)); i++)
    {
        char *curr = calloc(1, strlen(token) + 1);
        assert(curr);

        strcpy(curr, token);
        remove_whitespace(curr);
        operands[i] = curr;
    }

    *num_operands = i;

    for (int i = 0; i < *num_operands; i++)
    { //case where , within []
        if (operands[i][0] == '[' && operands[i][strlen(operands[i]) - 1] != ']')
        {
            char *updated = calloc(strlen(operands[i]) + strlen(operands[i + 1]) + 2, sizeof(char));
            assert(updated);

            strcat(updated, operands[i]);
            strcat(updated, ",");
            strcat(updated, operands[i + 1]);
            free(operands[i]);
            operands[i] = updated;
            //move everything over and free last one
            int j;
            for (j = i + 1; j < *num_operands - 1; j++)
            {
                operands[j] = realloc(operands[j], sizeof(operands[j + 1]));
                assert(operands[j]);

                strcpy(operands[j], operands[j + 1]);
            }
            free(operands[j]); //free the last
            *num_operands -= 1;
            i--;
        }
    }

    free(instruction);
    return operands;
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
    if (strcmp(reg, "PC") == 0)
    {
        return PC;
    }
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
    {"", INFINITY} //for iterating
};

enum Mnemonic convert_mnemonic(char *mnemonic)
{
    for (int i = 0; mnemonic_mapping[i].mnemonic != INFINITY; i++)
    {
        if (strcmp(mnemonic, mnemonic_mapping[i].str) == 0)
        {
            return mnemonic_mapping[i].mnemonic;
        }
    }
    perror("Bad Mnemonic");
    return -1;
}

uint32_t string_to_int(char *number)
{
    if (number[0] == '0' && number[1] == 'x')
    { //base16 case
        return strtol(number + 2, NULL, 16);
    }

    return strtol(number, NULL, 10);
}

void free_operands(char **operands, int num_operand)
{
    for (int i = 0; i < num_operand; i++)
    {
        free(operands[i]);
    }
    free(operands);
}

void free_tokens(tokens_t *tokens)
{
    free_operands(tokens->operands, tokens->num_operand);
    free(tokens);
}

void remove_whitespace(char *text)
{
    char *copy = strdup(text);
    //Remove from start
    int count = 0;
    for (int i = 0; text[i] == ' '; i++)
    {
        copy++;
        count++;
    }
    strcpy(text, copy);
    free(copy - count);
}