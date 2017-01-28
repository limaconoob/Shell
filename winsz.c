
#include "shell.h"
#include <sys/ioctl.h>

void WINSZ(unsigned short *winsz)
{ struct winsize wsz;
#ifdef __linux__
  ioctl(0, 0x5413, &wsz);
#else
  ioctl(0, 0x40000000 | (116 << 8) | 104 | ((sizeof(struct winsize) & 0x1FFF) << 16), &wsz);
#endif
  winsz[0] = wsz.ws_col;
  winsz[1] = wsz.ws_row; }
