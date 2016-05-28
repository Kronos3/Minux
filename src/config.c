/*
 * config.c
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
#include "config.h"
#include "file.h"

#ifndef MINUX_CFG_READ
#define MINUX_CFG_READ

section *
section_new (void)
{
  section          *buff =  malloc (sizeof(section));
  buff->variables        =  malloc (sizeof(mchar_a));
  buff->values           =  malloc (sizeof(mchar_a));
  buff->name             =  "";
  
  return buff;
}

section *
section_new_from_name (mstring name)
{
  section    *buff =  section_new ();
  buff->name       =  name;
}

config *
config_new (void)
{
  config          *buff =  malloc (sizeof(config));
  buff->sections        =  section_new ();
  buff->section_names   =  malloc (sizeof(mchar_a));
  buff->b_file          =  file_new ();
  
  return buff;
}

config *
config_new_from_file (file *in_file)
{
  config       *buff =  config_new ();
  buff->b_file       =  in_file;
  
  config_load (buff);
  
  return buff;
}

void
config_load (config* changing)
{
  int       curr;
  int       curr_var_num      =  0;
  mstring   curr_section_str;
  section   curr_section;
  int       curr_section_num  =  0;
  bool      section_inited    =  FALSE;
  
  for (curr = 0; curr != changing->b_file->length; c++)
  {
    mstring    line       =  changing->b_file->lines[curr];
    mstring    b_section  =  get_section (line);
    
    if (b_section != NULL)
    {
      if (section_inited)
      {
        changing->sections [curr_section_num] = curr_section;
      }
      curr_section_str  =  b_section;
      curr_section      =  section_new_from_name (curr_section_str);
      curr_var_num      =  0;
      section_inited    =  TRUE;
      changing->section_num++;
    }
    else
    {
      mchar_a buff                           = mstring_split (line, '=');
      curr_section->variables[curr_var_num]  = buff[0];
      curr_section->values[curr_var_num]     = buff[2];
      
      curr_var_num++;
    }
  }
}

config *
config_new_from_path (mstring path)
{
  return config_new_from_file (file_new_from_name (path, "r"))
}

bool
is_section (mstring line)
{
  if (line[0] == "\%" && line[mstring_get_length (line)] == "\%")
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
    return NULL;
  }
  
  return mstring_get_sub_py (line, 1, mstring_get_length (line) - 1);
}

void
conifg_append_section (config *changing, file *new)
{
  int       curr;
  int       curr_var_num      =  0;
  mstring   curr_section_str;
  section   curr_section;
  int       curr_section_num  =  changing->section_num + 1;
  bool      section_inited    =  FALSE;
  
  for (curr = 0; curr != new->length; c++)
  {
    mstring    line       =  new->lines[curr];
    mstring    b_section  =  get_section (line);
    
    if (b_section != NULL)
    {
      if (section_inited)
      {
        changing->sections [curr_section_num] = curr_section;
      }
      curr_section_str  =  b_section;
      curr_section      =  section_new_from_name (curr_section_str);
      curr_var_num      =  0;
      section_inited    =  TRUE;
    }
    else
    {
      mchar_a buff                           = mstring_split (line, '=');
      curr_section->variables[curr_var_num]  = buff[0];
      curr_section->values[curr_var_num]     = buff[2];
      
      curr_var_num++;
    }
  }
}

#endif
