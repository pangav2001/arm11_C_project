#include <stdlib.h>
#include <stdio.h>
#include "emulate_src/headers/memory.h"
#include "emulate_src/headers/registers.h"
#include "emulate_src/headers/parse_file.h"
#include "emulate_src/headers/decode.h"
#include "emulate_src/headers/data_processing.h"
#include "emulate_src/headers/emulate_output.h"

int main(int argc, char **argv)
{
  assert(argc == 2);

  //init memory and reg
  initialize_memory();
  initialize_registers();

  int bytes = read_in_binary(argv[1]);

  int32_t instruction;

  store_reg(PC, 8);

  while (get_reg(PC) - 8 < bytes)
  {
    instruction = get_memory(get_reg(PC) - 8, 4, BIG);
    if (instruction == 0) //all zero instruction
    {
      break;
    }
    store_reg(PC, get_reg(PC) + 4); //pc stores next instriction, but also 8 ahead so is 12 ahead
    decode(instruction);
  }

  print_registers();
  print_memory();

  //free memory and reg
  free_memory();
  free_registers();
  return EXIT_SUCCESS;
}
