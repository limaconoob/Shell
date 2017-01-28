
#include "lehrerin.h"
#include "outils.h"
#include <stdio.h>

void readder(t_term *)
{ char *line[1];
  while (GNL(1, line) > 0)
  { if (**line == 'q')
    { break; }
    else
    { printf("HI!\n"); }
    DEL((void**)line); }}

int main(int argc, char **argv)
{ static t_term term[1];
  TERM(&term);
  TINI();
  TEND((void*)0); }
