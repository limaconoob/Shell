
#include "shell.h"
#include "outils.h"

#include <stdio.h>

void readder(t_term *term)
{ char *line[1];
  while (GNL(1, line) > 0)
  { if (**line == 'q')
    { break; }
    else
    { printf("HI!\n"); }
    DEL((void**)line); }}

void hash_debug(t_hash *bonjour)
{ if (bonjour)
  { printf("HASHER::(%s, %s, 0x%x)\n", (*bonjour).exec, (*bonjour).path, (*bonjour).hash);
    hash_debug((*bonjour).lourd); 
    hash_debug((*bonjour).leger); }}

int main(int argc, char **argv, char **envp)
{ static t_term term[1];
  TERM(term, envp);

//DEBUG
  t_env *tmp = *((*term).env);
  while (tmp)
  { printf("ENV::(%s, %s)\n", (*tmp).nom, (*tmp).valeur);
    tmp = (*tmp).next; }

  printf("\n--------------------------------------------\n\n");

  printf("WINSZ::(%u, %u)\n", ((*term).winsz)[0], ((*term).winsz)[1]);
  printf("TOP_HASH::(%s, %s, 0x%x)\n", (*(*((*term).bin))).exec, (*(*((*term).bin))).path, (*(*((*term).bin))).hash);

  printf("\n--------------------------------------------\n\n");

  hash_debug(*((*term).bin));

  printf("\n--------------------------------------------\n\n");
//DEBUG

  TINI();
  readder(term);
  TEND((void*)0); }
