#include <stdio.h>
#include "machine.h"
#define PROGRAM_SIZE 8
#define DATA_SIZE 0

int main() {
  print_instruction(0xe0000666);
  printf("\n");

  return 0;
}
