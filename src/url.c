/*
 * url.c
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

#include "url.h"

URL *
url_new (void)
{
  URL              *buff;
  buff            =  malloc(sizeof(URL));
  buff->address   =  "";
  buff->host      =  "";
  buff->url       =  "";
  buff->name      =  "";
  buff->protocal  =  "";
  buff->is_valid  =  FALSE;
  buff->is_file   =  FALSE;
  
  return buff;
}

bool
address_valid (ip addr)
{
  struct     sockaddr_in   sa;
  int        result=       inet_pton(AF_INET, addr, &(sa.sin_addr));
  
  return result != 0;
}

ip
hostname_to_ip (hostname name)
{
  struct   hostent *he;
  struct   in_addr **addr_list;
  int      i;
  mchar    _ip[mstring_get_length(name)];
     
  if ( (he = gethostbyname( name ) ) == NULL) 
  {
    herror("gethostbyname");
    return NULL;
  }
 
  addr_list = (struct in_addr **) he->h_addr_list;
  
  for(i = 0; addr_list[i] != NULL; i++) 
  {
    strcpy(_ip , inet_ntoa(*addr_list[i]) );
    return &_ip[0];
  }
   
  return NULL;
}

URL *
url_new_from_string (mstring str)
{
  /* Example input (gentoo, lol)
   * https://packages.gentoo.org/packages/dev-python/pyopenssl
  */
  
  URL     *out = malloc(sizeof(URL));
  url_get (out, str);
  
  return out;
}

void
url_get (URL* in,
         mstring str)
{
  in                    =  url_new      ();
  in->url               =  str;
  int    index_protocal =  mstring_find (in->url, ':');
  
  if ( index_protocal != -1 )
  {
    index_protocal += 2;
    in->protocal = mstring_get_sub (in->url, 0, index_protocal);
    
    in->host = mstring_find_before ( mstring_get_sub_py (in->url, index_protocal, -1), '/' );
  }
  else
  {
    in->host = mstring_find_before (in->url, '/' );
  }
  
  if ( in->url[mstring_get_length(in->url)] != '/' )
  {
    in->is_file = TRUE;
  }
  
  if ( in->is_file )
  {
    in->name = basename (in->url);
  }
  else
  {
    in->name = dirname (in->url);
  }
  
  in->address     =   hostname_to_ip (in->host);
  in->is_valid    =   address_valid  (in->address);
}


