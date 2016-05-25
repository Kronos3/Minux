/*
 * standard_vars.c
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
#include "string.h"


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
