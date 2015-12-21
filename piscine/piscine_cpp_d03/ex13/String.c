/*
** String.c for  in /home/nicolaschr/rendu/piscine_cpp_d03/ex00
**
** Made by Nicolas Charvoz
** Login   <nicolaschr@epitech.net>
**
** Started on  Fri Jan  9 09:58:38 2015 Nicolas Charvoz
** Last update Fri Jan  9 15:45:27 2015 Nicolas Charvoz
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "String.h"

static void assign_c(String*, char const*);
static void assign_s(String*, String const*);
static void append_s(String*, String const*);
static void append_c(String*, char const*);
static char at(String *this, size_t pos);
static void clear(String *this);
static int size(String *this);
static int compare_s(String *this, const String *str);
static int compare_c(String *this, char const* str);
static size_t copy(String *this, char *s, size_t n, size_t pos);
static char const *c_str(String*);
static int empty(String *this);
static int find_s(String*, const String*, size_t);
static int find_c(String*, char const*, size_t);
static void insert_c(String *this, size_t pos, char const *str);
static void insert_s(String *this, size_t pos, String const *str);
static int to_int(String *this);
static String *split_s(String* this, char separator);
static char **split_c(String* this, char separator);

void StringInit(String *this, char const *s)
{
  if (s)
    this->str = strdup(s);
  else
    this->str = NULL;
  this->assign_s = &assign_s;
  this->assign_c = &assign_c;
  this->append_c = &append_c;
  this->append_s = &append_s;
  this->at = &at;
  this->clear = &clear;
  this->size = &size;
  this->compare_c = &compare_c;
  this->compare_s = &compare_s;
  this->copy = &copy;
  this->c_str = &c_str;
  this->empty = &empty;
  this->find_c = &find_c;
  this->find_s = &find_s;
  this->insert_c = &insert_c;
  this->insert_s = &insert_s;
  this->to_int = &to_int;
  this->split_c = &split_c;
  this->split_s = &split_s;
}

void StringDestroy(String *this)
{
  if (this->str)
    free(this->str);
  memset(this, 0, sizeof(String));
}

static void assign_s(struct string *this, String const *str)
{
  assign_c(this, str->str);
}

static void assign_c(String *this, char const *s)
{
  StringDestroy(this);
  StringInit(this, s);
}

static void append_s(String *this, String const *ap)
{
  append_c(this, ap->str);

}

static void append_c(String *this, char const *ap)
{
  if (ap)
    {
      this->str = realloc(this->str, ((strlen(ap) + strlen(this->str) + 2) * sizeof(char)));
      strcat(this->str, ap);
    }
}

static char at(String *this, size_t pos)
{
  if ((pos <= strlen(this->str) - 1))
    return (this->str[pos]);
  return (-1);
}

static void clear(String *this)
{
  if (this->str)
    memset(this->str, 0, strlen(this->str));
}

static int size(String *this)
{
  if (this->str)
    return (strlen(this->str));
  return (-1);
}

static int compare_s(String *this, const String *str)
{
  return (compare_c(this, str->str));
}

static int compare_c(String *this, char const* str)
{
  return (strcmp(this->str, str));
}

static size_t copy(String *this, char *s, size_t n, size_t pos)
{
  int i = 0;

  if (this && s)
    {
      while (n-- > 0 && pos < strlen(this->str))
	s[i++] = this->str[pos++];
      s[i] = '\0';
    }
  return (i);
}

static char const *c_str(String *this)
{
  return this->str;
}

static int empty(String *this)
{
  if (size(this) > 0)
    return (-1);
  return (1);
}

static int find_s(String *this, const String *str, size_t pos)
{
  return find_c(this, str->str, pos);
}

static int find_c(String *this, char const *str, size_t pos)
{
  if (strlen(this->str) > pos)
    {
      char *find = strstr(&this->str[pos], str);
      if (find)
	return (find - this->str);
    }
  return -1;
}

static void insert_c(String *this, size_t pos, char const *str)
{
  if (pos > strlen(this->str))
    return append_c(this, str);
  int length = strlen(str);
  if (pos < strlen(this->str))
    {
      this->str = realloc(this->str, (strlen(this->str) + strlen(str) + 2) * sizeof(char));
    }
  strcpy(&this->str[pos] + length, &this->str[pos]);
  strncpy(&this->str[pos], str, length);
}

static void insert_s(String *this, size_t pos, String const *str)
{
  insert_c(this, pos, str->str);
}

static int to_int(String *this)
{
  return atoi(this->str);
}

static String *split_s(String* this, char separator)
{
  printf("lol\n");
  char **tab = split_c(this, separator);
  int i = 0;

  printf("lol\n");
  while (tab[i++]);
  String *split = malloc(i * sizeof(String));
  while (i--)
    StringInit(&split[i], tab[i]);
  return split;
}

static char **split_c(String* this, char separator)
{
  char *str = strdup(this->str);
  char sep[2];
  sep[0] = separator;
  sep[1] = 0;
  char **tab;
  int i = 0;

  strtok(str, sep);
  while (strtok(NULL, sep))
    i++;
  tab = malloc((i + 1) * sizeof(char**));
  free(str);
  str = strdup(this->str);
  tab[0] = strtok(str, sep);
  i = 1;
  while ((tab[i++] = strtok(NULL, sep)));
  return tab;
}