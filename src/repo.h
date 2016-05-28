/*
 * repo.h
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
#include <time.h>
#include <curl/curl.h>
#include "extract.h"
#include "url.h"

#ifndef MINUX_REPO
#define MINUX_REPO

typedef struct
{
  URL       *url;
  mstring    sync_type;
  mstring    out_dir;
  mstring    out_file;
  int        time;
} repo;

repo *           repo_new                (void);

repo *           repo_new_from_url       (URL*, mstring);

repo *           repo_new_from_string    (mstring, mstring);

int              repo_sync               (repo*);

#endif
