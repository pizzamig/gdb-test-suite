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
  vvint = change ();
  return 0;
}
