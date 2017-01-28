
#ifndef SHELL_H
  #define SHELL_H

  #include <time.h>
  typedef struct timeval the_time;

  typedef enum e_error
  {
  } t_error;

  typedef struct s_env
  { char *nom;
    char *valeur;
    struct s_env *next;
  } t_env;

  typedef struct s_hash
  { int hash;
    char *bin;
    struct s_hash *lourd;
    struct s_hash *leger;
  } t_hash;

  typedef struct s_shell
  { char *contenu;
    the_time heure;
    char flag;
    struct s_shell *prev;
    struct s_shell *next;
  } t_shell;

  typedef struct s_term
  { unsigned short winsz[2];
    unsigned short cursor[2];
    t_shell *sh[1];
    t_hash *bin[1];
    t_env *env[1];
    char *paths[1];
  } t_term;

#endif
