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
#include <infovis/table/csv_loader.hpp>
#include <iostream>
#include <fstream>
#include <string>

namespace infovis {

using std::string;
using std::istream;

static void
skip_to_eol(istream& in)
{
  while (in) {
    char c = in.get();
    if (c == '\n')
      break;
  }
}

static void
ignore_line(istream& in)
{
  while (in.peek() == '#')
    skip_to_eol(in);
  skip_to_eol(in);
}

static string
read_to_eol(istream& in)
{
  char line[1024];

  while (in.peek() == '#')
    skip_to_eol(in);
  in.getline(line, 1024, '\n');
  return string(line, in.gcount());
}

static int
read_int(istream& in)
{
  int res;
  while (in.peek() == '#')
    skip_to_eol(in);
  in >> res;
  skip_to_eol(in);
  return res;
}

static bool
read_next_field(istream& in, char * line, int size)
{
  while (in.peek() == '#')
    skip_to_eol(in);
  while (in && size-- != 0) {
    char c = in.get();
    if (c == '\n' || c == ',') {
      *line++ = 0;
      return true;
    }
    else
      *line++ = c;
  }
  return false;
}

static column *
read_float_column(istream& in, int n)
{
  char line[1024];
  if (! read_next_field(in, line, 1024))
    return 0;
  
  FloatColumn * col = new FloatColumn(line);
  
  for (int i = 0; i < n; i++) {
    read_next_field(in, line, 1024);
    col->add_value(line);
  }
  return col;
}

bool tqd_table(const std::string& filename, table& t)
{
  std::ifstream in(filename.c_str());

  if (! in)
    return false;

  string title = read_to_eol(in);
  string static_attr = read_to_eol(in);
  string dynamic_attr = read_to_eol(in);
  int time_points = read_int(in);
  int records = read_int(in);

  ignore_line(in);		// ignore labels

  for (int i = 0; i < records; i++) {
    column * flt = read_float_column(in, time_points);
    if (flt != 0)
      t.add_column(flt);
  }

  return true;
}

} // namespace infovis
