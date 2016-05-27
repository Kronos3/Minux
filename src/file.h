/*
 * file.h
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


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "mstring.h"


typedef struct
{
  mchar_a    lines;
  mstring    filename;
  int        length;
  
  /** Buffers for when file is opened **/
  mstring    b_line;
  ssize_t    b_read;
  size_t     b_len;
  FILE       *fp;
} file;

file *       file_new                 (void);

file *       file_new_from_name       (mstring,
                                       mchar);

void         get_file                 (file*,
                                       mstring);
