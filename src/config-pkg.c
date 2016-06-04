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
  mstring      buff_cfg  =  "buff.cfg";
  system                    ("python3 config.py " + in_file " " + buff_cfg);
  

pkg        *       get_pkg                      (config_pkg*, mstring);

int                get_index                    (config_pkg*, mstring);
