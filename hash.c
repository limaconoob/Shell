
#include "shell.h"

static unsigned int hasher(char *str)
{ unsigned int hash = 5381;
  int i = 0;
  while (str[i])
  { hash = ((hash << 5) + hash) + str[i];
    i += 1; }
  return (hash); }

void HASH(t_hash **bin)
{}
