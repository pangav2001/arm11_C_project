#include <stdlib.h>
#include <stdio.h>
#include "memory.h"
#include "registers.h"
#include "parse_file.h"
#include "decode.h"
#include "data_processing.h"
#include "emulate_output.h"


int main(int argc, char **argv) {
  //make sure the user didn't mess up
  
  // testing branch
  assert(argc == 2);

  //init memory and reg
  initialize_memory();
  initialize_registers();

  int bytes = read_in_binary(argv[1]);
  // //printf("bytes: %d\n", bytes);

  int32_t instruction;

  store_reg(PC, 8);

  while (get_reg(PC) - 8 < bytes) {
    //printf("PC is: %d\n", get_reg(PC));
    instruction = get_memory(get_reg(PC) - 8, 4, BIG);
    if (instruction == 0) //all zero instruction
    {
      break;
    }
    store_reg(PC, get_reg(PC) + 4); //pc stores next instriction, but also 8 ahead so is 12 ahead
    decode(instruction);
  }
  
  // for(int i = 0; i < bytes; i+=4)
  // {
  //   instruction = get_memory(i, 4, BIG);
  //   if (instruction == 0) //all zero instruction
  //   {
  //     break;
  //   }
  //   store_reg(PC, get_reg(PC) + 4);
  //   decode(instruction);
    
  // }

  print_registers();
  print_memory();

  //free memory and reg
  free_memory();
  free_registers();
  return EXIT_SUCCESS;
}
