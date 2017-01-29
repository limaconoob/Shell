
#include "shell.h"
#include "outils.h"
#include <stdlib.h>
#include <unistd.h>

static t_shell *line_new(void)
{ t_shell *ret;
  if (!((ret = (t_shell*)malloc(sizeof(t_shell)))))
  { erreurs(Malloc, "ret dans line_new"); }
  if (!((*ret).contenu = (unsigned int*)malloc(1024 * sizeof(unsigned int))))
  { erreurs(Malloc, "contenu dans line_new"); }
  BZE((*ret).contenu, 1024 * sizeof(unsigned int));
  (*ret).len = 1024;
  BZE(&((*ret).heure), sizeof(t_shell) - (sizeof(int*) + sizeof(int)));
  return (ret); }

static void LINE(t_shell **line)
{ t_shell *prev;
  if (*line)
  { prev = *line;
    (**line).next = line_new();
    *line = (**line).next;
    (**line).prev = prev; }
  else
  { *line = line_new(); }}

static void push_char(t_shell **line, unsigned int m)
{ (**line).contenu[(**line).cursor] = m;
printf("CONTENU::(0x%x, %u) INDEX::%d\n", m, m, (**line).cursor);
  (**line).cursor += 1; }

void readder(t_term *term)
{ char line[1024];
  BZE(line, 1024);
  unsigned short attr[5];
  unsigned int m;
  int ret;
  int i;
  LINE((*term).logs);
  while ((ret = read(0, line, 1024)))
  { if (*line == '\n')
    { break; }
    i = 0;
    while (i < ret)
    { m = 0;
      if (!NCMP(&(line[i]), "\x1B[", 2))
      { if (line[i + 2] == 'A')
        { printf("Haut\n");
          i += 3; }
        else if (line[i + 2] == 'B')
        { printf("Bas\n");
          i += 3; }
        else if (line[i + 2] == 'C')
        { printf("Droite\n");
          i += 3; }
        else if (line[i + 2] == 'D')
        { printf("Gauche\n");
          i += 3; }
        else
        { i += 2;
          while (i < ret && (line[i] < 'A' || (line[i] > 'Z' && line[i] < 'a') || line[i] > 'z'))
          { i += 1; }}}
      else if ((line[i] & 0b11111000) == 0b11110000)
      { m = ((line[i] & 0x07) << 18) + ((line[i + 1] & 0x3F) << 12) + ((line[i + 2] & 0x3F) << 6) | (line[i + 3] & 0x3F);
        push_char((*term).logs, m);
        i += 4; }
      else if ((line[i] & 0b11110000) == 0b11100000)
      { m = ((line[i] & 0x0F) << 12) + ((line[i + 1] & 0x3F) << 6) + (line[i + 2] & 0x3F);
        push_char((*term).logs, m);
        i += 3; }
      else if ((line[i] & 0b11100000) == 0b11000000)
      { m |= ((line[i] & 0x1F) << 6);
        m |= (line[i + 1] & 0x3F);
        push_char((*term).logs, m);
        i += 2; }
      else
      { push_char((*term).logs, line[i]);
        i += 1; }}
    BZE(line, ret); }

// DEBUG
  int k = 0;
  unsigned char tmp[4];
  BZE(tmp, 4);
  write(0, "LINE::", 6);
  tmp[0] = 0x00e2;
  tmp[1] = 0x0082;
  tmp[2] = 0x00ac;
  write(1, tmp, 3);
  write(0, "\n", 1);
  BZE(tmp, 4);
  tmp[0] = 0xffe282ac;
  write(1, tmp, 3);
  write(0, "\n", 1);
  BZE(tmp, 4);
  while ((*(*((*term).logs))).contenu[k])
  { tmp[0] = (unsigned char)((*(*((*term).logs))).contenu[k] & 0xFF);
    tmp[1] = (unsigned char)(((*(*((*term).logs))).contenu[k] & 0xFF00) >> 8);
    tmp[2] = (unsigned char)(((*(*((*term).logs))).contenu[k] & 0xFF0000) >> 16);
    tmp[3] = (unsigned char)(((*(*((*term).logs))).contenu[k] & 0xFF000000) >> 24);
    write(0, tmp, LEN(tmp));
    write(0, tmp, 4);
printf("TMP! ::%s | LEN::%d\n0::%d | 1::%d | 2::%d | 3::%d\n", tmp, LEN(tmp), tmp[0], tmp[1], tmp[2], tmp[3]);
    printf("THE::0x%x\n", (*(*((*term).logs))).contenu[k]);
    BZE(tmp, 4);
    k += 1; }
  write(0, "\n", 1);
// DEBUG
}
