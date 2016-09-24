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
#ifndef TREEMAP2_PROPERTIES_HPP
#define TREEMAP2_PROPERTIES_HPP

#include <infovis/drawing/drawing.hpp>

#include <map>
#include <string>
#include <iostream>

using std::string;

namespace infovis {

class Font;

class Properties : public std::map<string,string>
{
public:
  typedef std::map<string,string> super;
  Properties() : defaults(0) { }
  Properties(const Properties * defs) : defaults(defs) { }

  string set(const string& key, const string& value) {
    string ret = get(key);
    (*this)[key] = value;
    return ret;
  }
  const_iterator find_value(const string& key) const {
    for (const Properties * prop = this; prop != 0; prop = prop->defaults) {
      const_iterator i = prop->find(key);
      if (i != prop->end())
	return i;
    }
    return end();
  }
  string get(const string& key) const {
    const_iterator i = find_value(key);
    if (i != end())
      return i->second;
    return "";
  }
  string get(const string& key, const string& def) const {
    const_iterator i = find_value(key);
    if (i != end())
      return i->second;
    return def;
  }
  int get_int(const string& key, int def = 0) const;
  double get_double(const string& key, double def = 0) const;
  Font * get_font(const string& key, Font * def = 0) const;
  Color get_color(const string& key, const Color& def) const;
  void load(std::istream& in);
  void load(const string& fname);
  void save(std::ostream& out);
  void save(const string& fname);
  static Properties * instance();
  static void load();
  static void save();

protected:
  const Properties * defaults;
  static Properties * instance_;
};

} // namespace infovis

#endif // TREEMAP2_PROPERTIES_HPP
