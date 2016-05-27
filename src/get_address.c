/*
 * get_address.c
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

#include "get_address.h"

mstring hostname_to_ip(mstring hostname)
{
  struct   hostent *he;
  struct   in_addr **addr_list;
  int      i;
  mchar    ip[mstring_get_length(hostname)];
     
  if ( (he = gethostbyname( hostname ) ) == NULL) 
  {
    herror("gethostbyname");
    return NULL;
  }
 
  addr_list = (struct in_addr **) he->h_addr_list;
  
  for(i = 0; addr_list[i] != NULL; i++) 
  {
    strcpy(ip , inet_ntoa(*addr_list[i]) );
    return &ip[0];
  }
   
  return NULL;
}
