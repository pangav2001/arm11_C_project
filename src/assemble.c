#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenizer.h"
#include "data_processing.h"
#include "branch.h"
//#include "sdt_assembly.h"
#include "multiply.h"

char **read_in_prog(char *filename, int *num_instr);

int main(int argc, char **argv)
{

  int num_instructions;
  char **instrucs = read_in_prog("../../arm11_testsuite/test_cases/beq02.s", &num_instructions);

  //First Pass

  int16_t address = 0; //The current address
  for (int i = 0; i < num_instructions; i++)
  {
    address = assign_label_address(instrucs[i], address);
  }

  //Second Pass

  //uint16_t start_location_for_data = address; //This is the current location from where we can store data
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
        // printf("DP\n");
        // printf("%u\n", data_process(tokens));
      }
      else if (tokens->mnemonic <= MLA)
      {
        //Multiply
        printf("MUL\n");
        printf("%u\n", multiply(tokens));
      }
      else if (tokens->mnemonic <= STR)
      {
        //SDT
        // printf("SDT\n");
      }
      else if (tokens->mnemonic <= B)
      {
        //branch
        // printf("B\n");
        //printf("%u\n", branch_assembly(tokens, address, ));
      }
      else if (tokens->mnemonic == LSL_M)
      {
        //special
        // printf("spec\n");
        tokens_t *tokens_lsl = (tokens_t *)malloc(sizeof(tokens_t));
        tokens_lsl->mnemonic = MOV;
        //Same number of arguments except for the extra Rn and lsl
        tokens_lsl->num_opcode = tokens->num_opcode + 2;
        tokens_lsl->opcodes = (char **)malloc(tokens_lsl->num_opcode * sizeof(char*));
        tokens_lsl->opcodes[0] = tokens_lsl->opcodes[1] = tokens->opcodes[0];
        tokens_lsl->opcodes[2] = "lsl";
        for (int i = 1; i < tokens->num_opcode; i++)
        {
          strcpy(tokens_lsl->opcodes[i + 2], tokens->opcodes[i]);
        }
        printf("%u\n", data_process(tokens_lsl));
        free_tokens(tokens_lsl);
      }
      else if (tokens->mnemonic == ANDEQ)
      {
        //Not supported
      }

      free_tokens(tokens);
      address += 4;
    }
  }

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
