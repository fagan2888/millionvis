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
#include <infovis/table/column.hpp>

namespace infovis {

column::column(const string& name)
  : name_(name),
    defined_()
{ }

column::column(const column& other)
  : name_(other.name_),
    defined_(other.defined_)
{ }


void
column::print(std::ostream& out) const
{
  out << name_ <<  "={" << std::endl;
  for (unsigned int i = 0; i < size(); i++) {
    out << get_value(i) << std::endl;
  }
  out << '}' << std::endl;
}

bool
column::read(std::istream& in)
{
  char buffer[1024];
  int i;

  in.getline(buffer, 1024);
  for (i = 0; buffer[i] != 0; i++) {
    if (buffer[i] == '=' &&
	buffer[i+1] == '{') {
      name_ = string(buffer, i);
      break;
    }
  }
  if (buffer[i] == 0)
    return false;

  while (in) {
    in.getline(buffer, 1024);
    if (buffer[0] == '}')
      break;
    add_value(buffer);
  }
  return true;
}


} // namespace infovis
