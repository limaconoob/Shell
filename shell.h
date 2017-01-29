
#ifndef SHELL_H
  #define SHELL_H

  #include <stdio.h>

  #include <sys/time.h>
  #include <time.h>
  typedef struct timeval the_time;

  typedef enum e_error
  { Malloc,
  } t_error;
  void erreurs(int flag, char *raison);

  typedef struct s_env
  { char *nom;
    char *valeur;
    struct s_env *next;
  } t_env;

  typedef struct s_hash
  { int hash;
    char *path;
    char *exec;
    struct s_hash *lourd;
    struct s_hash *leger;
  } t_hash;

  typedef struct s_shell
  { unsigned int *contenu;
    int len;
    the_time heure;
    int status_final;
    unsigned int cursor;
    struct s_shell *prev;
    struct s_shell *next;
  } t_shell;

  typedef struct s_term
  { unsigned short winsz[2];
    t_shell *logs[1];
    t_hash *bin[1];
    t_env *env[1];
    char *paths;
  } t_term;

///Initialisation
  void TERM(t_term *term, char **envp);
  void WINSZ(unsigned short *winsz);
  void ENV(t_term *term, char **envp);
  void HASH(t_hash **bin, char *paths);
  void LOG(t_shell **logs);

///Travail
  t_env *env_extract(char *env);
  char *find(t_hash **bin, char *exec);
  void openner(char *coucou, char *file, char *concat);
  void readder(t_term *term);

#endif
