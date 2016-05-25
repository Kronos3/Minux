/*
 * standard_vars.c
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

typedef int bool;

#define true 1
#define false 0


typedef struct      String             String;

String *            string_new                 (void);

String *            string_new_from_char       (char c);

String *            string_new_from_chars      (char *c);

String *            string_get_sub             (String *old,
                                                int start,
                                                int length);

String *            string_get_sub_py          (String *old,
                                                int start,
                                                int end);

char                string_index      (String *str,
                                       int index);

char                char_new                   (void);

char                char_new_from_char         (char c);
