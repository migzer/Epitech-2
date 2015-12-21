/*
** cmd_edi.c for zappy in /home/audibe_l/rendu/PSU_2014_zappy/sources/server
** 
** Made by Audibert Louis
** Login   <audibe_l@epitech.net>
** 
** Started on  Tue Jun 30 15:45:20 2015 Audibert Louis
** Last update Fri Jul  3 19:47:41 2015 Serge Heitzler
*/

#include "functions.h"

int		cmd_edi(t_egg *egg, t_list *clients)
{
  int		size_malloc;
  char		*str;

  size_malloc = 7 + istm(egg->id);
  str = malloc_and_memset(size_malloc);
  sprintf(str, "edi #%d\n", egg->id);
  send_data_to_gui(clients, str);
  free(str);
  return (SUCCESS);
}