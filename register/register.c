//#include <stdio.h>
static volatile int vint = 10;

int
change (void)
{
  return vint++;
}

int
main (void)
{
  register int vvint;
//  int a;
//   int vvint;
  vvint = change ();
//  a = vvint;
//   printf( "%d", vvint );
  return 0;
}
