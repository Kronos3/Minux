/*
 * extract.c
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



#include "extract.h"


int
copy_data (struct archive *ar,
           struct archive *aw)
{
  int           r;
  const void   *buff;
  size_t        size;
  off_t         offset;

  for (;;) {
    r = archive_read_data_block(ar, &buff, &size, &offset);
    
    if (r == ARCHIVE_EOF)
      return (ARCHIVE_OK);
    
    if (r < ARCHIVE_OK)
      return (r);
    
    r = archive_write_data_block(aw, buff, size, offset);
    
    if (r < ARCHIVE_OK) {
      fprintf(stderr, "%s\n", archive_error_string(aw));
      return (r);
    }
  }
}

int
extract (mstring filename,
         mstring dir)
{
  struct archive          *a;
  struct archive          *ext;
  struct archive_entry    *entry;
  int                      flags;
  int                      r;

  /* Select which attributes we want to restore. */
  flags    =  ARCHIVE_EXTRACT_TIME;
  flags   |=  ARCHIVE_EXTRACT_PERM;
  flags   |=  ARCHIVE_EXTRACT_ACL;
  flags   |=  ARCHIVE_EXTRACT_FFLAGS;

  a        =  archive_read_new();
  
  archive_read_support_format_all         (a);
  archive_read_support_filter_all         (a);
  ext      =  archive_write_disk_new      ();
  archive_write_disk_set_options          (ext, flags);
  archive_write_disk_set_standard_lookup  (ext);
  
  if ((r = archive_read_open_filename     (a, filename, 10240)))
    return 3; //File not found
  
  mkdir (dir, 0755);
  chdir (dir);
  
  for (;;) {
    r = archive_read_next_header(a, &entry);
    if (r == ARCHIVE_EOF)
      break;
    if (r < ARCHIVE_OK)
      fprintf(stderr, "%s\n", archive_error_string(a));
    if (r < ARCHIVE_WARN)
      return 1;
    r = archive_write_header(ext, entry);
    if (r < ARCHIVE_OK)
      fprintf(stderr, "%s\n", archive_error_string(ext));
    else if (archive_entry_size(entry) > 0) {
      r = copy_data(a, ext);
      if (r < ARCHIVE_OK)
        fprintf(stderr, "%s\n", archive_error_string(ext));
      if (r < ARCHIVE_WARN)
        return 2;
    }
    r = archive_write_finish_entry(ext);
    if (r < ARCHIVE_OK)
      fprintf(stderr, "%s\n", archive_error_string(ext));
    if (r < ARCHIVE_WARN)
      return 2;
  }
  archive_read_close(a);
  archive_read_free(a);
  archive_write_close(ext);
  archive_write_free(ext);
  exit(0);
}
