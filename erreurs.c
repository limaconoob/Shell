
#include "shell.h"
#include "outils.h"
#include <stdlib.h>
#include <unistd.h>

void erreurs(int flag, char *raison)
{ if (flag == Malloc)
  { write(2, raison, LEN(raison));
    exit(1); }
}

