#include <stdlib.h>
#include "memory.h"
#include "registers.h"


int main(int argc, char **argv) {
  //init memory and reg
  initialize_memory();
  initialize_registers();
  
  //free memory and reg
  free_memory();
  free_registers();
  return EXIT_SUCCESS;
}
