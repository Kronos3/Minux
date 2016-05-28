/*
 * repo.c
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


#include "repo.h"

repo *
repo_new (void)
{
  repo                *buff;
  buff              =  malloc(sizeof(repo));
  buff->sync_type   =  "";
  buff->time        =  0;
  buff->out_dir     =  "";
  buff->out_file    =  "";
  buff->url         =  url_new();
  return buff;
}

repo *
repo_new_from_url (URL* url,
                   mstring out_dir)
{
  repo       *buff =  repo_new ();
  buff->url        =  url;
  buff->out_dir    =  out_dir;
  
  return buff;
}

repo *
repo_new_from_string (mstring url,
                      mstring out_dir)
{
  URL          *b_url   =  url_new_from_string (url);
  repo         *b_repo  =  repo_new_from_url   (b_url, out_dir);
  
  return b_repo;
}

int
repo_sync (repo* sync_repo)
{
  if ((int)time(NULL) - sync_repo->time < 1200) /*Dont sync after 20 min*/
  {
    printf ("Last sync was less than 20 minutes ago\nexiting...\n");
    return 0;
  }
  
  strcat (sync_repo->out_file, sync_repo->out_dir);
  strcat (sync_repo->out_file, "/sync.db.tar.gz");
  truncate(sync_repo->out_file, 0);
  FILE *fp = fopen(sync_repo->out_file, "wb+");
  
  CURL *curl = curl_easy_init();
  if(curl) {
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, sync_repo->url->url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    printf ("Getting database archive from %s...", sync_repo->url->url);
    res = curl_easy_perform(curl);
    printf ("done\n");
    curl_easy_cleanup(curl);
    
    if ( res != CURLE_OK )
    {
      return 1;
    }
  }
  
  fclose (fp);
  
  int res = extract (sync_repo->out_file, sync_repo->out_dir);
  
  sync_repo->time = (int)time(NULL);
  return res;
}
