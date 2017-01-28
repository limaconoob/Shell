
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

void ENV(t_env **maitre, char **envp)
{ t_env *tmp;
  if (envp)
  { while (*envp)
    { if (*maitre)
      { (*tmp).next = env_extract(*envp);
        tmp = (*tmp).next; }
      else
      { tmp = env_extract(*envp);
        *maitre = tmp; }
      envp += 1; }}}
