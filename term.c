
#include "shell.h"
#include "outils.h"
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
typedef struct termios terms;

void TERM(t_term *term, char **envp)
{ WINSZ((*term).winsz);
  BZE((*term).cursor, sizeof(unsigned short) * 2);

  // TEMPORAIRE
  *((*term).logs) = NULL;
  // TEMPORAIRE

  *((*term).bin) = NULL;
  *((*term).env) = NULL;
  HASH((*term).bin);
  ENV((*term).env, envp); }

void TEND(terms *term)
{ static terms stock[1];
  if (term)
  { *stock = *term; }
  else
#ifdef __linux__ 
  { ioctl(0, 0x5402, stock); }}
#else
  { ioctl(0, 0x80000000 | (116 << 8) | 20 | ((sizeof(terms) & 0x1FFF) << 16), stock); }}
#endif

void TINI(void)
{ terms term;
#ifdef __linux__ 
  ioctl(0, 0x5401, &term);
#else
  ioctl(0, 0x40000000 | (116 << 8) | 19 | ((sizeof(terms) & 0x1FFF) << 16), &term);
#endif
  TEND(&term);
  term.c_lflag ^= ~(ICANON);
  term.c_lflag ^= ~(ECHO);
  term.c_cc[VMIN] = 1;
  term.c_cc[VTIME] = 0;
#ifdef __linux__ 
  ioctl(0, 0x5402, &term); }
#else
  ioctl(0, 0x80000000 | (116 << 8) | 20 | ((sizeof(terms) & 0x1FFF) << 16), &term); }
#endif
