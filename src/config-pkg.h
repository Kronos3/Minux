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
#include "file.h"

#ifndef __MINUX_CONFIG_PKG__
#define __MINUX_CONFIG_PKG__

typedef struct
{
  mstring     url;
  mstring     archive;
  mstring     size;
  mstring     type;
  mstring     name;
  mstring     version;
  mstring     release;
} pkg;

typedef struct
{
  file       *b_file;
  pkg       **packages;
  mchar_a     package_names;
  int         pkg_num;
} config_pkg;

pkg        *       pkg_new                      (void);

config_pkg *       config_pkg_new               (void);

config_pkg *       config_pkg_new_from_path     (mstring, mstring);

pkg        *       get_pkg                      (config_pkg*, mstring);

int                get_index                    (config_pkg*, mstring);

#endif
