#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  config.py
#  
#  Copyright 2016 Andrei Tumbar <atuser@Kronos>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  

import sys

def convert_version (__in):
  __in = __in[:__in.find(".tar.")]
  _type = __in[__in.rfind(".")+1:]
  __in = __in[:__in.rfind(".")]
  out = __in.rsplit("-", 2)
  out.insert (0, _type)
  return out

def convert_http (__in):
  b_out = []
  if (__in[:8] != "<a href="):
    return None
  __in = __in[8:].replace ("\"", "")
  b_out.append (__in[:__in.find (">")])
  __in = __in[__in.find (">")+1:]
  b_out.append (__in[:__in.find ("<")])
  __in = __in[__in.find ("<")+1:].replace ("</a>", "").strip()
  b_out.append (__in[__in.rfind (" ")+1:])
  return b_out

class http_src:
  
  def __init__ (self, __file, config):
    b_file = open (__file, "r").readlines()
    b_config = open(config, "w+")
    
    for line in b_file:
      buff = convert_http (line)
      if buff:
        ver_buff = convert_version (buff[1])
        b_config.write ("[%s]\n" % ver_buff [1])
        b_config.write ("url=%s\n" % buff[0])
        b_config.write ("archive=%s\n" % buff[1])
        b_config.write ("size=%s\n" % buff[2])
        b_config.write ("type=%s\n" % ver_buff[0])
        b_config.write ("name=%s\n" % ver_buff[1])
        b_config.write ("version=%s\n" % ver_buff[2])
        b_config.write ("release=%s\n" % ver_buff[3])
    
    b_config.close ()

if __name__ == "__main__":
  x = http_src (sys.argv[1], sys.argv[2])
