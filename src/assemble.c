#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenizer.h"
#include "data_processing.h"
#include "branch.h"
#include "sdt_assembly.h"
#include "multiply.h"
#include "output.h"
#include "assemble.h"

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
        save_instruction(assembled_program, address, multiply(tokens));
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

  for (int i = 0; i < 2; i++)
  {
    if ((input_file = fopen(filename, "r")) == NULL)
    {
      perror("input.txt");
      exit(1);
    }
    switch (i)
    {
    case 0:
      //Count instr
      while (fgets(buffer, sizeof(buffer), input_file) != NULL)
      {
        if (buffer[0] != '\n')
        {
          num_instructions++;
        }
      }
      break;
    case 1:
      *num_instr = num_instructions;
      instructions = calloc(num_instructions + 1, sizeof(char *)); //to allow to be null terminated
      int j = 0;
      while (fgets(buffer, sizeof(buffer), input_file) != NULL)
      {
        //int tst = strlen(buffer);
        instructions[j] = calloc(strlen(buffer), sizeof(char));
        strncpy(instructions[j], buffer, strlen(buffer));
        instructions[j][strlen(buffer) - 1] = '\0'; //remove \n
        j++;
      }
      break;
    }
    fclose(input_file);
  }
  instructions[num_instructions] = NULL;
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