/*
 * lstring.c
 * 
 * Copyright 2016 Andrei Tumbar <atuser@Kronos>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <string.h>
#include "lstring.h"


struct lstring
{
  char     *value;
};

/* Create a new empty string */
lstring *
string_new (void)
{
  lstring* buff;
  buff = &(lstring) {.value=""};
  
  return buff;
}

/* Create a new empty string */
lstring *
string_new_from_char (char c)
{
  char    *pchar;
  lstring  *buff;
  buff = string_new ();
  
  pchar = &c;
  
  buff->value = pchar;
  
  return buff;
}

lstring *
string_new_from_chars (char *c)
{
  lstring *buff;
  
  buff = &(lstring) {.value=c};
  return buff;
}

int
string_get_length (lstring *str)
{
  return sizeof(str->value);
}

char
string_index (lstring *str,
              int index)
{ 
  char    buff [string_get_length (str)];
  
  strcpy (buff, str->value);
  return buff[index];
}

lstring *
string_get_sub (lstring *old,
                int start,
                int length)
{
  int     size = string_get_length (old);
  char    buff_array [size];
  char    out_array [length-start];
  
  if (size < (start+length))
  {
    length = size-start;
  }
  
  int curr;
  
  for (curr = 0; curr != length; curr++)
  {
    out_array [curr] = buff_array[curr+start];
  }
  
  return string_new_from_chars (&out_array[0]);
}

lstring *
string_get_sub_py (lstring *old,
                   int start,
                   int end)
{
  int     size = string_get_length (old);
  char    buff_array [size];
  char    out_array [end];
  
  if (size < end)
  {
    end = size;
  }
  
  int index;
  int curr = 0;
  
  for (index = start; index <= end; index++, curr++)
  {
    out_array [curr] = buff_array[index];
  }
  
  return string_new_from_chars (&out_array[0]);
}

int
string_find (lstring* in,
             char find,
             int start)
{
  int   size = string_get_length (in);
  int   curr;
  char  buff [size];
  
  strcpy(buff, in->value);
  
  for (curr = start; curr != size; curr++)
  {
    char c = buff[curr];
    
    if (c == find)
    {
      return curr;
    }
  }
  
  return -1;
};

/*
lstring *
string_find_to (lstring* old,
                char c)
{
  
*/
