
#include "shell.h"
#include "outils.h"
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

static t_hash *hash_new(int hash, char *path, char *exec)
{ t_hash *ret;
  if (!((ret = (t_hash*)malloc(sizeof(t_hash)))))
  { erreurs(Malloc, "ret dans hash_new"); }
  (*ret).hash = hash;
  (*ret).path = DUP(path);
  (*ret).exec = LCHR((*ret).path, '/');
  (*ret).lourd = (void*)0;
  (*ret).leger = (void*)0;
  return (ret); }

static unsigned int hasher(char *str)
{ unsigned int hash = 5381;
  int i = 0;
  while (str[i])
  { hash = ((hash << 5) + hash) + str[i];
    i += 1; }
  return (hash); }

static void remplisshash(t_hash **bin, char *path, char *exec)
{ t_hash *tmp;
  int cmp;
  int hash = hasher(exec);
  if (*bin)
  { tmp = *bin;
    while (tmp)
    { if (hash > (*tmp).hash)
      { if ((*tmp).lourd)
        { tmp = (*tmp).lourd; }
        else
        { (*tmp).lourd = hash_new(hash, path, exec); }}
      else if (hash < (*tmp).hash)
      { if ((*tmp).leger)
        { tmp = (*tmp).leger; }
        else
        { (*tmp).leger = hash_new(hash, path, exec); }}
      else if ((cmp = CMP(exec, (*tmp).exec)))
      { if (cmp > 0)
        { if ((*tmp).lourd)
          { tmp = (*tmp).lourd; }
          else
          { (*tmp).lourd = hash_new(hash, path, exec); }}
        else
        { if ((*tmp).leger)
          { tmp = (*tmp).leger; }
          else
          { (*tmp).leger = hash_new(hash, path, exec); }}}
      else
      { break; }}}
  else
  { *bin = hash_new(hash, path, exec); }}

void openner(char *coucou, char *file, char *concat)
{ int i = 0;
  BZE(concat, 4096);
  if (coucou)
  { while (i < 4096 && *coucou)
    { concat[i] = *coucou;
      coucou += 1;
      i += 1; }
    if (i < 4096)
    { concat[i] = '/';
      i += 1; }}
  if (file)
  { while (i < 4096 && *file)
    { concat[i] = *file;
      file += 1;
      i += 1; }}}

char *find(t_hash **bin, char *exec)
{ t_hash *tmp = *bin;
  int cmp;
  int hash = hasher(exec);
  while (tmp)
  { if (hash > (*tmp).hash)
    { tmp = (*tmp).lourd; }
    else if (hash < (*tmp).hash)
    { tmp = (*tmp).leger; }
    else if ((cmp = CMP(exec, (*tmp).exec)))
    { if (cmp > 0)
      { tmp = (*tmp).lourd; }
      else
      { tmp = (*tmp).leger; }}
    else
    { printf("VIM_PATH::%s\n", (*tmp).path);
      return ((*tmp).path); }}
  return ((void*)0); }

static void dir_readder(t_hash **bin, char *path)
{ DIR *dir = opendir(path);
  char file[4096];
  int len;
  if (dir)
  { struct dirent *dp;
    struct stat sb;
    while ((dp = readdir(dir)))
    { len = LEN((*dp).d_name);
      if (CMP((*dp).d_name, ".") && CMP((*dp).d_name, ".."))
      { openner(path, (*dp).d_name, file);
        if (!lstat(file, &sb) && (sb.st_mode & 0xF000) == S_IFREG && (sb.st_mode & S_IXUSR))
        { remplisshash(bin, file, (*dp).d_name); }}}
    (void)closedir(dir); }}

void HASH(t_hash **bin, char *paths)
{ char buf[4096];
  int i = 0;
  if (paths)
  { BZE(buf, 4096);
    while (*paths)
    { if (*paths != ':' && i < 4095)
      { buf[i] = *paths;
        i += 1; }
      else
      { if (i)
        { dir_readder(bin, buf);
          BZE(buf, i); }
        i = 0; }
      paths += 1; }
    if (i)
    { dir_readder(bin, buf);
      BZE(buf, i); }}}
