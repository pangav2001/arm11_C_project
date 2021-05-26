#include <stdlib.h>
#include<stdio.h>
#include "memory.h"
#include "registers.h"
#include "parse_file.h"


int main(int argc, char **argv) {
  //init memory and reg
  initialize_memory();
  initialize_registers();

  //test for memory
  store_memory(1,2);
  store_memory(2, 4);
  int32_t m = get_memory(1,2);
  printf("memory test = %d\n", m);

  //test for registers
  store_reg(R12, 43);
  int r = get_reg(R12);
  printf("register test = %d\n", r);

  //test for read
  read_in_binary();
  printf("%d\n", get_memory(0, 4));
  
  //free memory and reg
  free_memory();
  free_registers();
  return EXIT_SUCCESS;
}
