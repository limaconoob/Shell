
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
typedef struct termios t_term;


void TEND(struct termios *term)
{ static t_term stock[1];
  if (term)
  { *stock = *term; }
  else
#ifdef __linux__ 
  { ioctl(0, 0x5402, stock); }}
#else
  { ioctl(0, 0x80000000 | (116 << 8) | 20 | ((sizeof(t_term) & 0x1FFF) << 16), stock); }}
#endif

void TINI(void)
{ struct termios term;
#ifdef __linux__ 
  ioctl(0, 0x5401, &term);
#else
  ioctl(0, 0x40000000 | (116 << 8) | 19 | ((sizeof(t_term) & 0x1FFF) << 16), &term);
#endif
  TEND(&term);
  term.c_lflag ^= ~(ICANON);
  term.c_lflag ^= ~(ECHO);
  term.c_cc[VMIN] = 1;
  term.c_cc[VTIME] = 0;
#ifdef __linux__ 
  ioctl(0, 0x5402, &term); }
#else
  ioctl(0, 0x80000000 | (116 << 8) | 20 | ((sizeof(t_term) & 0x1FFF) << 16), &term); }
#endif
