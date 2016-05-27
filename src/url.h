/*
 * url.h
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
#include <string.h> 
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <libgen.h>
#include "mstring.h"

#ifndef   MINUX_URL
#define   MINUX_URL

typedef mstring hostname;
typedef mstring ip;

typedef struct
{
  mstring    url;
  hostname   host;
  ip         address;
  mstring    name;
  mstring    protocal;
  bool       is_valid;
  bool       is_file; // If false then it is a directory
} URL;

ip           hostname_to_ip       (hostname);

bool         address_valid        (ip)

URL *        url_new              (void);

URL *        url_new_from_string  (mstring);

void         url_get              (URL*, mstring);

bool         url_ping             (URL*);
#endif


