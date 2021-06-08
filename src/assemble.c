#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenizer.h"

char** read_in_prog(char *filename);

int main(int argc, char **argv) {
  //test extracting label
  // char *label = "label:";
  // int t = assign_label_address(label, 0);
  // printf("%d", t);

  //test strtok_r
  // char *instruction = "ldr r2,[r0]";


  // struct tokens *token = tokenize_instruction(instruction);
  // //to free
  // free_tokens(token);

  //Read in file

  char **instrucs = read_in_prog("add01.s");
  printf("read in\n");


  return EXIT_SUCCESS;
}

//Maybe reuse from emulate but it uses memory which we do not need;
char** read_in_prog(char *filename) {
FILE *input_file;
char buffer[MAX_LINE_LENGTH];
int num_instructions = 0;
char **instructions;

for (int i = 0; i < 2; i++) {
  if ((input_file = fopen(filename, "r")) == NULL) {
    perror("input.txt"); exit;
  }
  switch(i) {
    case 0:
      //Count instr
      while(fgets(buffer, sizeof(buffer), input_file) != NULL) {
        num_instructions++;
      }
      break;
    case 1:
      instructions = calloc(num_instructions + 1, sizeof(char *)); //to allow to be null terminated
      int j = 0;
      while(fgets(buffer, sizeof(buffer), input_file) != NULL) {
        int tst = strlen(buffer);
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
