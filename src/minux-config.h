/*
 * config-parse.h
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

#ifndef __MINUX_CONFIG_PARSE__
#define __MINUX_CONFIG_PARSE__

typedef struct
{
  mstring     name;
  mchar_a     vars;
  mchar_a     vals;
  int         num;
} section;

typedef struct
{
  section   **sections;
  mchar_a     section_names;
  int         num;
} minux_config;

section      *         section_new               (void);

minux_config *         minux_config_new          (void);

minux_config *         minux_config_from_file    (file*);

minux_config *         minux_config_from_string  (mstring);

section      *         get_section               (minux_config*, mstring);

mstring                get_value                 (minux_config*, mstring, mstring);

#endif
