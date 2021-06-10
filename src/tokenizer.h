#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdint.h>
#include <stddef.h>
#include "emulate_src/registers.h"


#define MAX_LINE_LENGTH 511
#define MAX_OPCODE 4          //I think
#define MAX_MNEMONIC_LENGTH 6 //Based on what we need to implement

int16_t is_label(char *line);

//@address is the previous address returned by assign_label_address
// Since we do not increment if the line is a label
int16_t assign_label_address(char *line, int16_t address);

#define DATA_PROCESSING_INDEX 0
#define MULTIPLY_INDEX 20
#define SINGLE_DATA_TRANSFER_INDEX 25
#define BRANCH_INDEX 30
#define SPECIAL_INDEX 50

#define _1000 8
#define _1010 10
#define _1100 12


enum Mnemonic {
    //Data Processing
    AND = DATA_PROCESSING_INDEX,
    EOR,
    SUB,
    RSB,
    ADD,
    TST = DATA_PROCESSING_INDEX + _1000,
    TEQ,
    CMP,
    ORR = DATA_PROCESSING_INDEX + _1100,
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
    BGE = BRANCH_INDEX + _1010,
    BLT,
    BGT,
    BLE,
    B,
    //Special
    LSL = SPECIAL_INDEX,
    ANDEQ
};

typedef struct {
    char *str;
    enum Mnemonic mnemonic;
} Enum_Map;

static Enum_Map mnemonic_mapping[] = {
    "and", AND,
    "eor", EOR,
    "sub", SUB,
    "rsb", RSB,
    "add", ADD,
    "tst", TST,
    "teq", TEQ,
    "cmp", CMP,
    "orr", ORR,
    "mov", MOV,
    "mul", MUL,
    "mla", MLA,
    "ldr", LDR,
    "str", STR,
    "beq", BEQ,
    "bne", BNE,
    "bge", BGE,
    "blt", BLT,
    "bgt", BGT,
    "ble", BLE,
    "b", B,
    "lsl", LSL,
    "andeq", ANDEQ,
    NULL, NULL //for iterating
};

typedef struct {
    enum Mnemonic mnemonic;
    int num_opcode;
    char **opcodes;
} tokens;

tokens* tokenize_instruction(char *line);

enum Mnemonic extract_mnemonic(char** line);

enum Register_Names convert_register(char* reg);

enum Mnemonic convert_mnemonic(char* mnemonic);

void free_tokens(struct tokens* tokens);

#endif