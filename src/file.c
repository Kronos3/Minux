/*
 * file.c
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


#include "file.h"


file *
file_new (void)
{
  file            *buff;
  
  buff            =  malloc(sizeof(file));
  buff->filename  =  "";
  buff->length    =  0;
  buff->fp        =  NULL;
  buff->b_read    =  0;
  buff->b_len    =  0;
  
  return    buff;
}

file *
file_new_from_name (mstring name, mchar type)
{
  file       *out = file_new();
  out->fp     =fopen(name, mstring_new_from_char(type));
  int        curr;
  
  /** Check if file exists **/
  if (out->fp == NULL)
  {
    return NULL;
  }
  
  for (curr = 0; (out->b_read = getline(&out->b_line, &out->b_len, out->fp) ) != -1; curr++)
  {
    out->lines[curr] = out->b_line;
  }
  
  out->length = out->b_len;
  
  fclose (out->fp);
  
  /** Clear the line buffer **/
  if (out->b_line)
  {
    free(out->b_line);
  }
  
  /** Reset the buffers **/\
  out->b_read  =  0;
  out->b_len  =  0;
  
  return out;
}
