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
#ifndef INFOVIS_DRAWING_POINT_VEC_IO_HPP
#define INFOVIS_DRAWING_POINT_VEC_IO_HPP

#include <iostream>
#include <typeinfo>
#include <cstring>
#include <infovis/drawing/point_vec.hpp>

namespace infovis {

#define CFOREACH for (int i = 0; i < Dim; i++)

template <int Dim, class Coord>
inline std::ostream&
operator << (std::ostream& out, const point_<Dim, Coord>& p)
{
  out << typeid(p).name() <<"(";
  //out << "point<" << Dim << ">::(" << p[0];
  CFOREACH { out << ((i == 0) ? "" : ",") << p[i]; }
  return out << ')';
}

template <int Dim, class Coord>
inline std::istream&
operator >> (std::istream& in, point_<Dim, Coord>& p)
{
  in.ignore(strlen(typeid(p).name())+1);
  CFOREACH { in >> p[i]; in.ignore(1); }
  return in;
}

template <int Dim, class Coord>
inline std::ostream&
operator << (std::ostream& out, const vector_<Dim, Coord>& v)
{
  out << typeid(v).name() <<"(";
  CFOREACH { out << (i==0? "" : ",") << v[i]; }
  return out << ')';
}

template <int Dim, class Coord>
inline std::istream&
operator >> (std::istream& in, vector_<Dim, Coord>& v)
{
  in.ignore(strlen(typeid(p).name()+1));
  CFOREACH { in >> v[i]; in.ignore(1); }
  return in;
}
#undef CFOREACH
} // namespace

#endif // INFOVIS_DRAWING_POINT_VEC_IO_HPP
