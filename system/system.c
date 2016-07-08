#include <stdlib.h>
#include <stdio.h>

int main() {
  printf("system call returned code=%d\n", system("/bin/ls"));
  return 0;
}

