#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdint.h>

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

#endif