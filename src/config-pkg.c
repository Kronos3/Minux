/*
 * config-pkg.c
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
#include "config-pkg.h"

variable *
variable_new (void)
{
  variable        *buff =  malloc (sizeof(variable));
  buff->name            =  mstring_new ();
  buff->value           =  mstring_new ();
  
  return buff;
}

variable *
variable_new_from_str (mchar_a in)
{
  variable    *buff     =  variable_new ();
  buff->name            =  get_section (in [0]);
  buff->value           =  in [1];
  
  return buff;
}

config_pkg *
config_pkg_new (void)
{
  config_pkg        *buff =  malloc (sizeof(config_pkg));
  buff->variables         =  malloc (sizeof(variable*));
  buff->variable_names    =  mchar_a_new ();
  buff->b_file            =  file_new ();
  buff->variable_num    =  0;
  
  return buff;
}

config_pkg *
config_pkg_new_from_file (file* _file)
{
  config_pkg      *buff     =  config_pkg_new ();
  buff->b_file              =  _file;
  mchar_a         *b_vars   =  mchar_a_split (buff->b_file->lines, "\n", buff->b_file->length);
  int              curr     =  1;
  
  for (; curr != atoi(b_vars[0][0]); curr++)
  {
    variable      *b_var        =  variable_new_from_str (b_vars[curr]);
    buff->variables[curr]       =  b_var;
    buff->variable_names[curr]  =  b_var->name;
  }
  
  buff->variable_num = curr;
  
  return buff;
}

config_pkg *
config_pkg_new_from_path (mstring path)
{
  file        *b_file   = file_new_from_name (path, "r");
  config_pkg  *b_config = config_pkg_new_from_file (b_file);
  
  return b_config;
}

bool
is_section (mstring line)
{
  if (line[0] == '\%' && line[mstring_get_length (line)] == '\%')
  {
    return TRUE;
  }
  
  return FALSE;
}

mstring
get_section (mstring line)
{
  if (!is_section (line))
  {
    return line;
  }
  
  return mstring_get_sub_py (line, 1, mstring_get_length (line) - 1);
}

variable *
get_variable (config_pkg *get,
              mstring key)
{
  int curr;
  
  for (curr = 0; curr != get->variable_num; curr++)
  {
    if (get->variable_names[curr] == key)
    {
      return get->variables[curr];
    }
  }
  
  return NULL;
}

int
get_index    (config_pkg *get,
              mstring key)
{
  int curr;
  
  for (curr = 0; curr != get->variable_num; curr++)
  {
    if (get->variable_names[curr] == key)
    {
      return curr;
    }
  }
  
  return -1;
}
