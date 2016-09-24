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
#include <Properties.hpp>
#include <infovis/drawing/Font.hpp>
#include <infovis/drawing/color_io.hpp>
#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <strstream>

namespace infovis {

int
Properties::get_int(const string& key, int def) const
{
  const_iterator i = find(key);
  if (i != end())
    return atoi(i->second.c_str());
  return def;
}

double
Properties::get_double(const string& key, double def) const
{
  const_iterator i = find(key);
  if (i != end())
    return atof(i->second.c_str());
  return def;
}

Font *
Properties::get_font(const string& key, Font * def) const
{
  const string& name = get(key + ".name", "Arial");
  const string& style = get(key + ".style", "plain");
  float size = get_double(key + ".size", 12.0);
  
  return Font::create(name, style, size);
}

Color
Properties::get_color(const string& key, const Color& def) const
{
  const_iterator i = find(key);
  if (i == end())
    return def;
  string color = i->second;
  if (color.substr(0, 5) != "Color") {
    const_iterator i = find(color);
    if (i == end())
      return def;
    color = i->second;
  }
  Color c;
  std::istrstream in(color.c_str(), color.size());
  in >> c;
  return c;
}

void
Properties::load(std::istream& in)
{
  char buffer[2048];
  while (in) {
    in.getline(buffer, 2048);
    string line(buffer);
    if (line.length() == 0)
      continue;
    if (line[0] == '#' || line[0] == '!')
      continue;
    size_t prop_start = 0;
    size_t prop_end = 0;
    size_t val_start = 0;
    size_t val_end = 0;
    size_t i = 0;
    for (; i < line.length(); i++) {
      if (! isspace(line[i])) {
	break;
      }
    }
    prop_start = i;
    for (; i < line.length(); i++) {
      if (line[i] == '\\') {
	if (i == (line.length()-1)) {
	  line.erase(i);
	  break;
	}
	else {
	  line.erase(i, 1);	// remove \\ and don't test next char
	}
      }
      else if (isspace(line[i])) {
	break;
      }
    }
    prop_end = i;
    if (prop_start == prop_end)	// end of line reached
      continue;
    for (; i < line.length(); i++) {
      if (! isspace(line[i])) {
	break;
      }
    }
    val_start = i;
    for (; i < line.length(); i++) {
      if (line[i] == '\\') {
	if (i == (line.length()-1)) {
	  line.erase(i);
	  break;
	}
	else {
	  line.erase(i, 1);	// remove \\ and don't test next char
	}
      }
      else if (isspace(line[i])) {
	break;
      }
    }
    val_end = i;
    set(line.substr(prop_start, prop_end), line.substr(val_start, val_end));
  }
}

void
Properties::load(const string& fname)
{
  std::ifstream in(fname.c_str());
  load(in);
}

static void
print_quoted(std::ostream& out, const string& s)
{
  for (int i = 0; i < s.length(); i++) {
    if (s[i] < 32 ||
	(s[i] > 0x7e && s[i] < 0xa0))
      out << '\\';
    out << s[i];
  }
}

void
Properties::save(std::ostream& out)
{
  for (const_iterator i = begin(); i != end(); i++) {
    print_quoted(out, i->first);
    out << "\t";
    print_quoted(out, i->second);
    out << std::endl;
  }
}

void
Properties::save(const string& fname)
{
  std::ofstream out(fname.c_str());
  save(out);
}

Properties * Properties::instance_;

Properties *
Properties::instance()
{
  if (instance_ == 0)
    instance_ = new Properties();
  return instance_;
}

void
Properties::load()
{
  instance()->load(".properties");
  const char * home = getenv("HOME");
  if (home == 0)
    return;
  string path(home);
  path.append("/.properties");
  instance()->load(path);
}

void
Properties::save()
{
  const char * home = getenv("HOME");
  if (home == 0)
    home = ".";
  string path(home);
  path.append("/.properties");
  std::ofstream out(path.c_str());
  instance()->save(out);
}

}
