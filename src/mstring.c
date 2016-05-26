/*
 * mstring.c
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
#include "mstring.h"



/* Create a new empty string */
mstring
mstring_new (void)
{
  return "";
}

/* Create a new empty string */
mstring
mstring_new_from_char (mchar c)
{
  mstring  buff;
  
  buff = &c;
  
  return buff;
}

mstring
mstring_new_from_chars (char *c)
{
  return c;
}

int
mstring_get_length (mstring str)
{
  return strlen(str);
}

mchar
mstring_index  (mstring str,
                int index)
{
  return str[index];
}

mstring
mstring_get_sub  (mstring old,
                  int start,
                  int length)
{
  int      size = mstring_get_length (old);
  mchar    out_array [length-start];
  
  if (size < (start+length))
  {
    length = size-start;
  }
  
  int curr;
  
  for (curr = 0; curr != length; curr++)
  {
    out_array [curr] = old[curr+start];
  }
  
  return mstring_new_from_chars (&out_array[0]);
}

mstring
mstring_get_sub_py (mstring old,
                    int start,
                    int end)
{
  int      size = mstring_get_length (old);
  mchar    out_array [end];
  
  if (size < end)
  {
    end = size;
  }
  
  int index;
  int curr = 0;
  
  for (index = start; index <= end; index++, curr++)
  {
    out_array [curr] = old[index];
  }
  
  return mstring_new_from_chars (&out_array[0]);
}

int
mstring_find (mstring in,
              mchar find,
              int start)
{
  int   size = mstring_get_length (in);
  int   curr;
  char  buff [size];
  
  strcpy(buff, in);
  
  for (curr = start; curr != size; curr++)
  {
    char c = buff[curr];
    
    if (c == find)
    {
      return curr;
    }
  }
  
  return -1;
}


mstring
mstring_find_to  (mstring* old,
                  mchar c)
{
  char buff_a [mstring_find (old, c)];
  
  for ( 
