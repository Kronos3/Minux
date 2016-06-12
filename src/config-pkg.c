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


#include "minux-config.h"
#include "config-pkg.h"


pkg *
pkg_new (void)
{
  pkg        *buff =  malloc       (sizeof(pkg*));
  buff->url        =  mstring_new  ();
  buff->archive    =  mstring_new  ();
  buff->size       =  mstring_new  ();
  buff->type       =  mstring_new  ();
  buff->name       =  mstring_new  ();
  buff->version    =  mstring_new  ();
  buff->release    =  mstring_new  ();
  
  return buff;
}

config_pkg *
config_pkg_new (void)
{
  config_pkg       *buff =  malloc       (sizeof(config_pkg*));
  buff->b_file           =  file_new     ();
  buff->packages         =  malloc       (sizeof(pkg**));
  buff->package_names    =  mchar_a_new  ();
  buff->pkg_num          =  0;
  
  return buff;
}

config_pkg *
config_pkg_new_from_path (mstring in_file)
{
  config_pkg     *buff      =  config_pkg_new      ();
  minux_config   *b_config  =  minux_config_new    ();
  buff->b_file              =  file_new_from_name  (in_file, "r");
  int             curr      =  0;
  
  mstring         buff_cfg  =  "buff.cfg";
  system                       (concat (concat (concat ("python3 config.py ", in_file), " "), buff_cfg));
  
  b_config                  =  minux_config_from_file (buff->b_file);
  
  for (; b_config->sections [curr]; curr++, buff->pkg_num++)
  {
    pkg  *curr_pkg     =  pkg_new ();
    curr_pkg->url      =  get_value (b_config, b_config->sections [curr]->name, "url");
    curr_pkg->archive  =  get_value (b_config, b_config->sections [curr]->name, "archive");
    curr_pkg->size     =  get_value (b_config, b_config->sections [curr]->name, "size");
    curr_pkg->type     =  get_value (b_config, b_config->sections [curr]->name, "type");
    curr_pkg->name     =  get_value (b_config, b_config->sections [curr]->name, "name");
    curr_pkg->version  =  get_value (b_config, b_config->sections [curr]->name, "version");
    curr_pkg->release  =  get_value (b_config, b_config->sections [curr]->name, "release");
    
    buff->packages       [curr]  =  curr_pkg;
    buff->package_names  [curr]  =  curr_pkg->name;
  }
  
  return buff;
}

pkg *
get_pkg (config_pkg* in_config, mstring name)
{
  int curr;
  for (curr = 0; curr != in_config->pkg_num; curr++)
  {
    mstring p_curr = in_config->package_names [curr];
    if (p_curr == name)
    {
      return in_config->packages [curr];
    }
  }
  
  return NULL;
}

int
get_index (config_pkg* in_config, mstring name)
{
  int curr;
  for (curr = 0; curr != in_config->pkg_num; curr++)
  {
    mstring p_curr = in_config->package_names [curr];
    if (p_curr == name)
    {
      return curr;
    }
  }
  
  return -1;
}
