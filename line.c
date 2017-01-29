
#include "shell.h"
#include "outils.h"
#include <stdlib.h>

static t_shell *line_new(void)
{ t_shell *ret;
  if (!((ret = (t_shell*)malloc(sizeof(t_shell)))))
  { erreurs(Malloc, "ret dans line_new"); }
  if (!((*ret).contenu = (int*)malloc(1024 * sizeof(int))))
  { erreurs(Malloc, "contenu dans line_new"); }
  BZE((*ret).contenu, 1024 * sizeof(int));
  (*ret).len = 1024;
  BZE(&((*ret).heure), sizeof(t_shell) - (sizeof(int*) + sizeof(int)));
  return (ret); }

void LINE(t_shell **line)
{ t_shell *prev;
  if (*line)
  { prev = *line;
    (*line).next = line_new();
    *line = (*line).next;
    (*line).prev = prev; }
  else
  { *line = line_new(); }}

void push_char(t_shell **line, int m)
{ (**line).contenu[(**line).cursor] = m;
}
