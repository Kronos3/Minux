/*
 * minux-config.c
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


#include "minux-config.h"

section *
section_new (void)
{
  section       *buff  =  malloc (sizeof (section*));
  buff->name           =  mstring_new ();
  buff->vars           =  mchar_a_new ();
  buff->vals           =  mchar_a_new ();
  buff->num            =  0;
  
  return buff;
};

minux_config *
minux_config_new (void)
{
  minux_config    *buff  =  malloc (sizeof (minux_config*));
  buff->sections         =  malloc (sizeof (section**));
  buff->section_names    =  mchar_a_new ();
  buff->num            =  0;
  
  return buff;
};

minux_config *
minux_config_from_file (file* __file)
{
  int            curr;
  section       *curr_sec;
  bool           made      =  FALSE;
  minux_config  *b_out     =  minux_config_new ();
  
  for (curr = 0; curr != __file->length; curr++)
  {
    mstring line = __file->lines [curr];
    if (line[0] == '#' || strcmp (line, "") == 0 || strcmp (line, "\n") == 0)
    {
      continue;
    }
    
    if (line[0] == '[')
    {
      if (made)
      {
        b_out->num++;
        b_out->sections[b_out->num]        =  curr_sec;
        b_out->section_names [b_out->num]  =  curr_sec->name;
      }
      
      curr_sec = section_new ();
      curr_sec->name = mstring_get_sub_py (line, 1, -1);
      continue;
    }
    
    mchar_a                 b_splt   =  mstring_split (line, '=');
    curr_sec->vars [curr_sec->num]   =  b_splt [0];
    curr_sec->vals [curr_sec->num]   =  b_splt [1];
    curr_sec->num++;
  }
  
  return b_out;
}

minux_config *
minux_config_from_string (mstring _file_name)
{
  file         *b_file  =  file_new_from_name      (_file_name, "r");
  minux_config *buff    =  minux_config_from_file  (b_file);
  
  return buff;
}

section *
get_section  (minux_config* _in_config, mstring section_name)
{
  return _in_config->sections [mchar_a_find (_in_config->section_names, section_name)];
}

mstring
get_value (minux_config* _in_config, mstring section_name, mstring var)
{
  section       *sec = get_section (_in_config, section_name);
  return sec->vals [mchar_a_find (sec->vars, var)];
}
