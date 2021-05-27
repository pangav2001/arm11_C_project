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
  assert(argc == 2);

  //init memory and reg
  initialize_memory();
  initialize_registers();

  int bytes = read_in_binary(argv[1]);

  int noOfInstructions = bytes / 4;

  for(int i = 0; i < noOfInstructions; i+=4)
  {
    decode(get_memory(i, 4));
  }

  print_registers();
  print_memory();

  //free memory and reg
  free_memory();
  free_registers();
  return EXIT_SUCCESS;
}
