#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "assemble_src/headers/tokenizer.h"
#include "assemble_src/headers/data_processing.h"
#include "assemble_src/headers/branch.h"
#include "assemble_src/headers/sdt_assembly.h"
#include "assemble_src/headers/multiply.h"
#include "assemble_src/headers/output.h"
#include "assemble_src/headers/assemble.h"

char **read_in_prog(char *filename, int *num_instr);

int main(int argc, char **argv)
{

  int num_instructions;
  char **instrucs = read_in_prog(argv[1], &num_instructions);

  Hash_Table *hash_table = new_table(2000); //How many

  //First Pass

  int16_t address = 0; //The current address
  for (int i = 0; i < num_instructions; i++)
  {
    address = assign_label_address(instrucs[i], address, hash_table);
  }

  //Second Pass

  uint16_t start_location_for_data = address; //This is the current location from where we can store data
  //such as offsets too large to fit into the instruction

  uint32_t *assembled_program = calloc(2 * num_instructions, sizeof(uint32_t)); //Cannot have more than 2* in output

  address = 0;
  for (int i = 0; i < num_instructions; i++)
  {
    if (!is_label(instrucs[i]))
    {
      printf("%s\n", instrucs[i]);
      tokens_t *tokens = tokenize_instruction(instrucs[i]);

      if (tokens->mnemonic <= MOV)
      {
        //Data Processing
        save_instruction(assembled_program, address, data_process(tokens));
        printf("DP\n");
        printf("%u\n", data_process(tokens));
      }
      else if (tokens->mnemonic <= MLA)
      {
        //Multiply
        save_instruction(assembled_program, address, assemble_multiply(tokens));
        // printf("MUL\n");
        // printf("%u\n", multiply(tokens));
      }
      else if (tokens->mnemonic <= STR)
      {
        //SDT
        save_instruction(assembled_program, address, sdt_assembly(tokens, address, &start_location_for_data, assembled_program));
        //printf("SDT\n");
      }
      else if (tokens->mnemonic <= B)
      {
        //branch
        save_instruction(assembled_program, address, branch_assembly(tokens, address, hash_table));
        // printf("B\n");
        // printf("%u\n", branch_assembly(tokens, address, hash_table));
      }
      else if (tokens->mnemonic == LSL_M)
      {
        //special
        // printf("spec\n");

        char *instruction = malloc(MAX_LINE_LENGTH * sizeof(char));
        sprintf(instruction, "mov %s,%s,lsl %s", tokens->opcodes[0], tokens->opcodes[0], tokens->opcodes[1]);
        tokens_t *tokens_lsl = tokenize_instruction(instruction);
        save_instruction(assembled_program, address, data_process(tokens_lsl));
        free_tokens(tokens_lsl);
        free(instruction);
      }
      else if (tokens->mnemonic == ANDEQ)
      {
        save_instruction(assembled_program, address, 0);
      }
      else
      {
        //Not supported
      }

      free_tokens(tokens);
      address += 4;
    }
  }

  write_to_binary(argv[2], assembled_program, start_location_for_data / 4);
  free_table(hash_table);
  free(assembled_program);

  return EXIT_SUCCESS;
}

//Maybe reuse from emulate but it uses memory which we do not need;
char **read_in_prog(char *filename, int *num_instr)
{
  FILE *input_file;
  char buffer[MAX_LINE_LENGTH];
  int num_instructions = 0;
  char **instructions;

  if ((input_file = fopen(filename, "r")) == NULL)
  {
    perror("input.txt");
    exit(1);
  }

  //Count instr
  instructions = calloc(1000, sizeof(char *)); //to allow to be null terminated
  int j = 0;
  while (fgets(buffer, sizeof(buffer), input_file) != NULL)
  {
    if (buffer[0] != '\n')
    {
      printf("buffer: %s", buffer);
      num_instructions++;
      instructions[j] = calloc(strlen(buffer), sizeof(char));
      strncpy(instructions[j], buffer, strlen(buffer));
      instructions[j][strlen(buffer) - 1] = '\0'; //remove \n
      j++;
    }
  }
  *num_instr = num_instructions;
  instructions = realloc(instructions, (num_instructions + 1) * sizeof(char *));

  printf("Num of instructions: %d\n", num_instructions);

  instructions[num_instructions] = NULL;
  fclose(input_file);
  return instructions;
}

void save_instruction(uint32_t *assembled_program, uint16_t address, uint32_t data)
{
  assembled_program[address / 4] = data;
}

void write_reserved_memory(uint32_t *assembled_program, int *next_avaliable_address, uint32_t reserved_data)
{
  assembled_program[*next_avaliable_address] = reserved_data;
  *next_avaliable_address += 4;
}