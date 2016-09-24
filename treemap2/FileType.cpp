/* -*- C++ -*-
 *
 * Copyright (C) 2002 Jean-Daniel Fekete
 * 
 * This file is part of MillionVis.
 * 
 * MillionVis is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 * 
 * MillionVis is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with MillionVis; see the file COPYING.  If not, write to the
 * Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA. 
 */
#include "FileType.hpp"
#include <algorithm>
#include <fstream>
#include <cstring>

FileType::FileType() {}
FileType::~FileType() { }

void
FileType::setCode(const string& ext, int code)
{
  extmap[ext] = code;
}

int
FileType::getCode(const string& ext) const
{
  Map::const_iterator i = extmap.find(ext);
  if (i == extmap.end())
    return type_unknown;
  return i->second;
}

int
FileType::extensionCount() const
{
  return extmap.size();
}

const string&
FileType::getExtension(int index) const
{
  Map::const_iterator i = extmap.begin();
  std::advance(i, index);
  return i->first;

}

FileType::Type
FileType::fileType(const string& filename) const
{
  if (filename.empty())
    return Type(false, false,type_unknown);
  if (*filename.rbegin() == '/')
    return Type(false, true, type_directory);
  string::size_type p = filename.find_last_of(".");
  if (p == string::npos)
    p = string::size_type(-1);
  Map::const_iterator i = extmap.find(filename.substr(p+1));
  if (i == extmap.end())
    return Type(false, false, type_unknown);
  int code = i->second;
  if (code == type_directory)
    return Type(false, true, code);
  else if (code != type_compressed)
    return Type(false, false, code);
  string::size_type p2 = filename.find_last_of(".", p-1);
  if (p2 == string::npos)
    return Type(false, false, code);
  i = extmap.find(filename.substr(p2+1, p - p2 - 1));
  if (i == extmap.end())
    return Type(false, false, code);
  return Type(false, true, i->second);
}

void
FileType::save(const string& filename) const
{
  std::ofstream out(filename.c_str());
  
  for (Map::const_iterator i = extmap.begin(); i != extmap.end(); i++)
    out << i->first << '\t' << i->second << std::endl;
}

void
FileType::load(const string& filename)
{
  std::ifstream in(filename.c_str());

  while (in) {
    string ext;
    int num;
    in >> ext >> num;
    setCode(ext, num);
  }
}
