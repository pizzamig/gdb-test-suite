#include <stdlib.h>
#include <stdio.h>

main() {
  printf("system call returned code=%d\n", system("/bin/ls"));
}

