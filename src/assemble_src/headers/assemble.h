#ifndef _ASSEMBLE_H_
#define _ASSEMBLE_H_

#include <stdint.h>

void save_instruction(uint32_t *assembled_program, uint16_t address ,uint32_t data);

char **read_in_prog(char *filename, int *num_instr);

#endif