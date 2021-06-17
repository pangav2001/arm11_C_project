#ifndef _TOKENIZER_H_ASSEMBLER_
#define _TOKENIZER_H_ASSEMBLER_

#include <stdint.h>
#include <stddef.h>
#include "../../emulate_src/headers/registers.h"
#include "hash_table.h"

#define MAX_LINE_LENGTH 511
#define MAX_OPERAND 4          //I think
#define MAX_MNEMONIC_LENGTH 6 //Based on what we need to implement

int16_t is_label(char *line);

//@address is the previous address returned by assign_label_address
// Since we do not increment if the line is a label
int16_t assign_label_address(char *line, int16_t address, Hash_Table *table);

#define DATA_PROCESSING_INDEX 0
#define MULTIPLY_INDEX 20
#define SINGLE_DATA_TRANSFER_INDEX 25
#define BRANCH_INDEX 30
#define SPECIAL_INDEX 50

#define B_1000 8
#define B_1010 10
#define B_1100 12

enum Mnemonic
{
    //Data Processing
    AND = DATA_PROCESSING_INDEX,
    EOR,
    SUB,
    RSB,
    ADD,
    TST = DATA_PROCESSING_INDEX + B_1000,
    TEQ,
    CMP,
    ORR = DATA_PROCESSING_INDEX + B_1100,
    MOV,
    //Multiply
    MUL = MULTIPLY_INDEX,
    MLA,
    //Single Data Transfer
    LDR = SINGLE_DATA_TRANSFER_INDEX,
    STR,
    //Branch
    BEQ = BRANCH_INDEX,
    BNE,
    BGE = BRANCH_INDEX + B_1010,
    BLT,
    BGT,
    BLE,
    B,
    //Special
    LSL_M = SPECIAL_INDEX,
    ANDEQ
};

typedef struct
{
    char *str;
    enum Mnemonic mnemonic;
} Enum_Map;

// typedef struct
// {
//     enum Mnemonic mnemonic;
//     int num_opcode;
//     char **opcodes;
// } tokens_t;

typedef struct
{
    enum Mnemonic mnemonic;
    int num_operand;
    char **operands;
} tokens_t;

tokens_t *tokenize_instruction(char *line);

enum Mnemonic extract_mnemonic(char **line);

char** extract_operands(char* line, int *num_operand);

enum Register_Names convert_register(char *reg);

enum Mnemonic convert_mnemonic(char *mnemonic);

uint32_t string_to_int(char *number);

void free_operands(char **operands, int num_operand);

void free_tokens(tokens_t *tokens_t);

void remove_whitespace(char* text);

#endif