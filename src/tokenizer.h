#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdint.h>

int16_t is_label(char *line);

//@address is the previous address returned by assign_label_address
// Since we do not increment if the line is a label
int16_t assign_label_address(char *line, int16_t address);

enum Mnemonic {
    ADD,
    SUB,
    RSB,
    AND,
    EOR,
    ORR,
    MOV,
    TST,
    TEQ,
    CMP,
    MUL,
    MLA,
    LDR,
    STR,
    BEQ,
    BNE,
    BGE,
    BLT,
    BGT,
    BLE,
    B,
    LSL,
    ANDEQ
};

struct tokens {
    enum Mnemonic mnemonic;
    int num_opcode;
    char *opcodes;
};

struct tokens tokenize_instruction(char *line);

void extract_mnemonic(char** line);

enum Register_Names convert_register(char* reg);

#endif