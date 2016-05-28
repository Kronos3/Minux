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

typedef struct
{
  mstring    name;
  mstring    value;
} variable;

typedef struct
{
  file       *b_file;
  variable  **variables;
  mchar_a     variable_names;
  int         variable_num;
} config_pkg;

variable   *       variable_new                 (void);

variable   *       variable_new_from_str        (mchar_a);

variable   *       get_variable                 (config_pkg*, mstring);

int                get_index                    (config_pkg*, mstring);

config_pkg *       config_pkg_new               (void);

config_pkg *       config_pkg_new_from_file     (file*);

config_pkg *       config_pkg_new_from_path     (mstring);

bool               is_section                   (mstring);

mstring            get_section                  (mstring);
