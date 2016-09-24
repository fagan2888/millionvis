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
#ifndef FileType_hpp
#define FileType_hpp

#include <infovis/alloc.hpp>
#include <map>
#include <string>
#include <cstring>
using std::string;

struct string_nocase_less {
  bool operator () (const std::string& s1, const std::string& s2) const {
    int min_sz = s1.size() < s2.size() ? s1.size() : s2.size();
    int ret = strnicmp(s1.c_str(), s2.c_str(), min_sz);
    if (ret < 0) return true;
    if (ret > 0) return false;
    return s1.size() < s2.size();
  }
};

struct string_nocase_eq {
  bool operator() (const std::string& s1, const std::string& s2) const {
    if (s1.size() != s2.size())
      return false;
    return strnicmp(s1.c_str(), s2.c_str(), s1.size()) == 0;
  }
};

class FileType {
public:
  FileType();
  ~FileType();

  enum {
    type_unknown,
    type_compressed,
    type_directory,
  };
  struct Type {
    bool is_compressed:1;
    bool is_directory:1;
    int code:30;

    Type(bool comp, bool dir, int c)
      : is_compressed(comp), is_directory(dir), code(c) {}
    int getCode() const { return code; }
    bool isCompressed() const { return is_compressed; }
    bool isDirectory() const { return is_directory; }
  };
  void setCode(const string& ext, int code);
  int getCode(const string& ext) const;

  int extensionCount() const;
  const string& getExtension(int index) const;

  Type fileType(const string& filename) const;

  void load(const string& filename);
  void save(const string& filename) const;
protected:
  typedef std::map<string,int, string_nocase_less> Map;
  Map extmap;
};

#endif
