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

pkg *
pkg_new (void)
{
  pkg        *buff =  malloc (sizeof(pkg));
  buff->src_name        =  mstring_new ();
  buff->pkg_name        =  mstring_new ();
  buff->version         =  mstring_new ();
  buff->revision        =  mstring_new ();
  buff->size            =  0;
  
  return buff;
}

pkg *
pkg_new_from_str (mstring in)
{
  pkg         *buff     =  pkg_new ();
  mchar_a      b_str    =  get_section_pkg (in);
  buff->src_name        =  b_str[0];
  buff->pkg_name        =  b_str[1];
  buff->version         =  b_str[2];
  buff->revision        =  b_str[3];
  buff->size            =  b_str[4];
  
  return buff;
}

config_pkg *
config_pkg_new (void)
{
  config_pkg        *buff =  malloc (sizeof(config_pkg));
  buff->packages          =  malloc (sizeof(pkg*));
  buff->package_names     =  mchar_a_new ();
  buff->b_file            =  file_new ();
  buff->pkg_num    =  0;
  
  return buff;
}

config_pkg *
config_pkg_new_from_file (file* _file)
{
  config_pkg      *buff     =  config_pkg_new ();
  buff->b_file              =  _file;
  int              curr     =  0;
  int              var      =  0;
  
  for (; curr != buff->b_file->length; curr++)
  {
    mchar_a   b_arr             =  get_section_pkg (buff->b_file->lines[curr]);
    
    if (b_arr == NULL)
    {
      continue;
    }
    
    pkg      *b_var             =  pkg_new_from_str (buff->b_file->lines[curr]);
    buff->packages[var]        =  b_var;
    buff->package_names[var]   =  b_var->pkg_name;
    var++;
  }
  
  buff->pkg_num = curr;
  
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
is_section_pkg (mstring line)
{
  if (strcmp(mstring_get_sub (line, 0, 16), "<script>addRow(\"") == 0 && line[16] != '.')
  {
    return TRUE;
  }
  
  return FALSE;
}

mchar_a
parse_name (mstring in)
{
  int      rev_dev =  mstring_rfind (in, '-');
  int      ver_dev =  mstring_rfind (mstring_get_sub_py(in, 0, rev_dev-1), '-');
  mchar_a  buff    =  mchar_a_new ();
  buff[0]          =  mstring_get_sub_py (in, 0, ver_dev - 1);
  buff[1]          =  mstring_get_sub_py (in, ver_dev, rev_dev - 1);
  buff[2]          =  mstring_get_sub_py (in, rev_dev, mstring_find_start (in, '.', rev_dev));
  
  return buff;
}

mchar_a
get_section_pkg (mstring line)
{
  
  mchar_a     b_out     =  mchar_a_new ();
  mstring     src_name;
  mstring     size;
  int         num       =  0;
  int         curr      =  16;
  
  if (!is_section_pkg (line))
  {
    return NULL;
  }
  
  num       =  mstring_find_start     (line, '\"', curr);
  src_name  =  mstring_get_sub_py     (line, curr, num);
  
  curr      =  num;
  num       =  mstring_find_start_num (line, '\"', curr, 4) + 1;
  size      =  mstring_find_before (mstring_get_sub_py (line, num, -1), '\"');
  
  mchar_a buff = parse_name(src_name);
  b_out[0] = src_name;
  b_out[1] = buff[0];
  b_out[2] = buff[1];
  b_out[3] = buff[2];
  b_out[4] = size;
  
  return b_out;
}

pkg *
get_pkg (config_pkg *get,
              mstring key)
{
  int curr;
  
  for (curr = 0; curr != get->pkg_num; curr++)
  {
    if (get->package_names[curr] == key)
    {
      return get->packages[curr];
    }
  }
  
  return NULL;
}

int
get_index    (config_pkg *get,
              mstring key)
{
  int curr;
  
  for (curr = 0; curr != get->pkg_num; curr++)
  {
    if (get->package_names[curr] == key)
    {
      return curr;
    }
  }
  
  return -1;
}
