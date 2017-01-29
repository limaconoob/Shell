
#include "shell.h"
#include "outils.h"
#include <unistd.h>

#include <stdio.h>

void readder(t_term *term)
{ char line[1024];
  BZE(line, 1024);
  unsigned short attr[5];
  unsigned int m;
  int ret;
  int i;
  while ((ret = read(1, line, 1024)))
  { if (*line == 'q')
    { break; }
    i = 0;
    while (i < ret)
    { if (!NCMP(&(line[i]), "\x1B[", 2))
      { if (line[i + 2] == 'A')
        { printf("Haut\n"); }
        else if (line[i + 2] == 'B')
        { printf("Bas\n"); }
        else if (line[i + 2] == 'C')
        { printf("Droite\n"); }
        else if (line[i + 2] == 'D')
        { printf("Gauche\n"); }
        i += 3; }
      else if ((line[i] & 0b11111000) == 0b11110000)
      { m = ((u1 & 0x07) << 18) | ((u2 & 0x3F) << 12) | ((u3 & 0x3F) << 6) | (u4 & 0x3F);
        push((*term).line, m);
        i += 4; }
      else if ((line[i] & 0b11110000) == 0b11100000)
      {
        i += 3; }
      else if ((line[i] & 0b11100000) == 0b11000000)
      {
        i += 2; }
      else
      { printf("HI!\n");
        i += 1; }}
    BZE(line, ret); }}

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

  find((*term).bin, "vim");

  printf("\n--------------------------------------------\n\n");
//DEBUG

  TINI();
  readder(term);
  TEND((void*)0); }
