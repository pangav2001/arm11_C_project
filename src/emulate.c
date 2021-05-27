#include <stdlib.h>
#include<stdio.h>
#include "memory.h"
#include "registers.h"
#include "parse_file.h"
#include "decode.h"
#include "data_processing.h"


int main(int argc, char **argv) {
  // //init memory and reg
  initialize_memory();
  initialize_registers();

  // //test for memory
  // store_memory(1,2);
  // store_memory(2, 4);
  // int32_t m = get_memory(1,2);
  // printf("memory test = %d\n", m);

  // //test for registers
  // store_reg(R12, 43);
  // int r = get_reg(R12);
  // printf("register test = %d\n", r);

  // // //test for read
  // // read_in_binary();
  // // printf("%d\n", get_memory(0, 4));

  // printf("%d\n", extract_bits(39, 1, 7));
  
  //Test for data processing
  // int32_t e = 7;
  // int32_t r = shift(LSR, e, 2, 0);
  // printf("%d\n", r);

  //Test for flags
  set_flag(N);
  int32_t cpsr = extract_bits(get_reg(CPSR),28,31);
  printf("%d\n",get_flag(N));
  set_flag(Z);
  cpsr = extract_bits(get_reg(CPSR),28,31);
  printf("%d\n",get_flag(Z));
  set_flag(C);
  cpsr = extract_bits(get_reg(CPSR),28,31);
  printf("%d\n",get_flag(C));
  set_flag(V);
  cpsr = extract_bits(get_reg(CPSR),28,31);
  printf("%d\n",get_flag(V));
  reset_flag(V);
  cpsr = extract_bits(get_reg(CPSR),28,31);
  printf("%d\n",get_flag(V));
  reset_flag(C);
  cpsr = extract_bits(get_reg(CPSR),28,31);
  printf("%d\n",get_flag(C));
  reset_flag(Z);
  cpsr = extract_bits(get_reg(CPSR),28,31);
  printf("%d\n",get_flag(Z));
  reset_flag(N);
  cpsr = extract_bits(get_reg(CPSR),28,31);
  printf("%d\n",get_flag(N));



  //free memory and reg
  free_memory();
  free_registers();
  return EXIT_SUCCESS;
}

// 7 6 5 4 3 2 1 0
// 0 0 1 0 0 1 1 1