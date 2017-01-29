
#include <stdlib.h>

int TLN(char **tab)
{ int i = 0;
  while (tab[i])
  { i += 1; }
  return (i); }

void DEL(void** data)
{ free(*data);
  *data = (void*)0; }

int LEN(char *str)
{ int i = 0;
  while (*(str + i))
  { i += 1; }
  return (i); }

char *LCHR(char *str,  char find)
{ if (str)
  { int i = LEN(str);
    while (i + 1)
    { if (str[i] == find)
      { i += 1;
        return (&(str[i])); }
      i -= 1; }}
  return ((void*)0); }

char *DUP(char *str)
{ int i = 0;
  char *ret;
  if (!((ret = (char*)malloc(LEN(str) + 1))))
  { return ((void*)0); }
  while (*(str + i))
  { ret[i] = *(str + i);
    i += 1; }
  ret[i] = 0;
  return (ret); }

char *SUB(char *str, int start, int len)
{ char *ret;
  int i = 0;
  if (!((ret = (char*)malloc(len + 1))))
  { return ((void*)0); }
  while (i < len)
  { ret[i] = *(str + start + i);
    i += 1; }
  ret[i] = 0;
  return (ret); }

void NCPY(void *ptr1, void *ptr2, int size)
{ while (size)
  { ((unsigned char *)ptr1)[size - 1] = ((unsigned char *)ptr2)[size - 1];
    size -= 1; }}

void BZE(void *ptr, int size)
{ while (size)
  { ((unsigned char *)ptr)[size - 1] = 0;
    size -= 1; }}

int CMP(void *ptr1, void *ptr2)
{ int i = 0;
  while (((unsigned char*)ptr1)[i] && ((unsigned char*)ptr2)[i] && ((unsigned char*)ptr1)[i] == ((unsigned char*)ptr2)[i])
  { i += 1; }
  return (((unsigned char*)ptr1)[i] - ((unsigned char*)ptr2)[i]); }

int NCMP(void *ptr1, void *ptr2, int size)
{ if (size > 0)
  { int i = 0;
    while (i < size && ((unsigned char*)ptr1)[i] == ((unsigned char*)ptr2)[i])
    { i += 1; }
    if (i != size)
    { return (((unsigned char*)ptr1)[i] - ((unsigned char*)ptr2)[i]); }}
  return (0); }
