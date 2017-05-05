
#include "shell.h"
#include "outils.h"
#include <stdlib.h>
#include <unistd.h>

static void fall_exp(t_shell *line)
{ unsigned int *grosser;
  (*line).fall += 1;
  grosser = (unsigned int*)malloc(80 * sizeof(unsigned int) * (*line).fall);
  if (!grosser)
  { erreurs(Malloc, "contenu dans fall_exp"); }
  BZE(grosser, 80 * sizeof(unsigned int) * (*line).fall);
  if ((*line).contenu)
  { NCPY(grosser, (*line).contenu, (*line).len);
    free((*line).contenu); }
  (*line).contenu = grosser; }

static t_shell *line_new(void)
{ t_shell *ret;
  if (!((ret = (t_shell*)malloc(sizeof(t_shell)))))
  { erreurs(Malloc, "ret dans line_new"); }
  BZE(ret, sizeof(t_shell));
  fall_exp(ret);
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

static void push_char(t_shell *line, unsigned int m)
{ (*line).len += 1;
  if ((*line).len == ((*line).fall * 80) - 1)
  { fall_exp(line); }
  (*line).contenu[(*line).cursor] = m;
  write(0, (char*)&m, 4);
  (*line).cursor += 1; }

void readder(t_term *term)
{ unsigned char line[1024];
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
      { m |= line[i];
        m |= (line[i + 1] << 8);
        m |= (line[i + 2] << 16);
        m |= (line[i + 3] << 24);
        push_char((*(*term).logs), m);
        i += 4; }
      else if ((line[i] & 0b11110000) == 0b11100000)
      { m |= line[i];
        m |= (line[i + 1] << 8);
        m |= (line[i + 2] << 16);
        push_char((*(*term).logs), m);
        i += 3; }
      else if ((line[i] & 0b11100000) == 0b11000000)
      { m |= line[i];
        m |= (line[i + 1] << 8);
        push_char((*(*term).logs), m);
        i += 2; }
      else
      { push_char((*(*term).logs), line[i]);
        i += 1; }}
    BZE(line, ret); }

// DEBUG
  int k = 0;
  unsigned char tmp[4];
  BZE(tmp, 4);
  write(0, "\nLINE::", 7);
  while (k < (*(*((*term).logs))).len)
  { if ((*(*((*term).logs))).contenu[k])
    { write(0, (char*)&((*(*((*term).logs))).contenu[k]), 4); }
    else
    { write(0, "Q", 1); }
    k += 1; }
  write(0, "\n", 1);
  printf("SHELL! len::%d, curs::%d, fall::%d\n", (*(*((*term).logs))).len, (int)(*(*((*term).logs))).cursor, (int)(*(*((*term).logs))).fall);
// DEBUG
}
