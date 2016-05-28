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
#include "file.h"

#ifndef MINUX_CFG_READ
#define MINUX_CFG_READ

typedef struct
{
  mchar_a     variables;
  mchar_a     values;
  mstring     name;
} section;

typedef struct
{
  file       *b_file;
  section    *sections;
  mchar_a     section_names;
  int         section_num;
} config;

section *          section_new              (void);

section *          section_new_from_name    (mstring);

config  *          config_new               (void);

config  *          config_new_from_file     (file*);

config  *          config_new_from_path     (mstring);

bool               is_section               (mstring);

mstring            get_section              (mstring);

void               config_load              (config*);

void               conifg_append_section    (config*,
                                             file*);
#endif
