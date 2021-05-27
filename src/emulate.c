#include <stdlib.h>
#include<stdio.h>
#include "memory.h"
#include "registers.h"
#include "parse_file.h"
#include "decode.h"
#include "data_processing.h"
//#include "data_processing.c"


int main(int argc, char **argv) {
  // //init memory and reg
  initialize_memory();
  initialize_registers();

  //Tests for immediate operant
  int32_t e = 1325;
  store_reg(10,123456789);
  int32_t r = immediate_operand(e, 0, 0);
  printf("%d\n", r);
  printf("%d\n", get_reg(10));


  //free memory and reg
  free_memory();
  free_registers();
  return EXIT_SUCCESS;
}
