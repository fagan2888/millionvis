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
#ifndef INFOVIS_DRAWING_COLOR_IO_HPP
#define INFOVIS_DRAWING_COLOR_IO_HPP

#include <infovis/drawing/color.hpp>
#include <string>
#include <iostream>

namespace infovis {

template <class T, class S>
std::ostream& operator << (std::ostream& out, const color_type<T,S>& color)
{
  typedef color_type<T,S> Color;
  out << Color::name() << ":";
  for (int i = 0; i < Color::last_channel; i++) {
    if (i != 0)
      out << "/";
    out << double(color[i]);
  }
  return out << " ";
}

template <class T, class S>
std::istream& operator >> (std::istream& in, color_type<T,S>& color)
{
  typedef color_type<T,S> Color;
  int i;
  const char * n = Color::name();

  for (i = 0; n[i] != 0; i++) {
    if (in.get() != n[i])
      return in;		// don't read
  }

  if (in.get() != ':')
    return in;
  for (i = 0; i < Color::last_channel; i++) {
    double c;
    if (i != 0)
      in.ignore(2, '/');
    in >> c;
    color[i] = c;
  }
  in.ignore(1, ' ');
  return in;
}

} // namespace infovis

#endif // INFOVIS_DRAWING_COLOR_IO_HPP
