
#include "shell.h"
#include "outils.h"
#include <stdlib.h>

static int bon_format_env(char *env)
{ int i = 0;
  while (env[i])
  { if (env[i] == '=')
    { if (!i)
      { return (-2); }
      else if (!env[i + 1])
      { return (-3); }
      else
      { return (i); }}
    i += 1; }
  return (-1); }

t_env *env_extract(char *env)
{ int i = 0;
  if (env && *env)
  { int flag = bon_format_env(env);
    if (flag > 0)
    { t_env *ret;
      if (!((ret = (t_env*)malloc(sizeof(t_env)))))
      { erreurs(Malloc, "ret dans env_extract"); }
      while (env[i] && env[i] != '=')
      { i += 1; }
      (*ret).nom = SUB(env, 0, i);
      i += 1;
      (*ret).valeur = SUB(env, i, LEN(&(env[i])));
      (*ret).next = (void*)0; 
      return (ret); }
    else if (flag == -1)
    { /* pas de '=' */ }
    else if (flag == -2)
    { /* rien avant le '=' */ }
    else if (flag == -3)
    { /* rien après le '=' */ }}
  else
  { /* absence de phrase */ }
  return ((void*)0); }

void ENV(t_term *term, char **envp)
{ t_env *tmp;
  if (envp)
  { while (*envp)
    { if (*((*term).env))
      { (*tmp).next = env_extract(*envp);
        if ((*tmp).next)
        { tmp = (*tmp).next; }}
      else
      { tmp = env_extract(*envp);
        *((*term).env) = tmp; }
      if (tmp && !NCMP((*tmp).nom, "PATH", LEN((*tmp).nom)))
      { (*term).paths = (*tmp).valeur;
        HASH((*term).bin, (*tmp).valeur); }
      envp += 1; }}}
