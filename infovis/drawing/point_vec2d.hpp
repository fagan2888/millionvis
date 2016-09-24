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
#ifndef INFOVIS_DRAWING_POINT_VEC2D_HPP
#define INFOVIS_DRAWING_POINT_VEC2D_HPP

#include <infovis/drawing/point_vec.hpp>

namespace infovis {

/**
 * Point in 2D template
 */
template <class Coord>
struct point2d : point_<2, Coord>
{
  typedef point_<2, Coord> super;

  point2d() { }

  point2d(const point2d& p) : point_<2, Coord>(p) { }

  template <class Coord2>
  point2d(const point_<2, Coord2>& p) : super(p) {}

#ifndef __GNUG__
  template <class Coord2>
  explicit point2d(const vector_<2,Coord2>& v) : super(v) {}
#endif

  point2d(const Coord& x, const Coord& y) {
    at(0) = x;
    at(1) = y;
  }

};

template <class Coord>
inline const Coord&
x(const point_<2, Coord>& p) { return p[0]; }

template <class Coord>
inline const Coord&
y(const point_<2, Coord>& p) { return p[1]; }

template <class Coord>
inline const Coord&
set_x(point_<2, Coord>& p, const Coord& v) {
  return p[0] = v;
}

template <class Coord>
inline const Coord&
set_y(point_<2, Coord>& p, const Coord& v) {
  return p[1] = v;
}

/**
 * Vector in 2D template
 */
template <class Coord>
struct vector2d : vector_<2, Coord>
{
  typedef vector_<2, Coord> super;

  vector2d () { }

  vector2d(const vector2d& v) : super(v) {}

  template <class Coord2>
  vector2d(const vector_<2, Coord2> & v) : super(v) {}

#ifndef __GNUG__
  template <class Coord2>
  explicit vector2d(const point_<2,Coord2>& p) : super(p) {}
#endif

  vector2d(const Coord& dx, const Coord& dy) {
    at(0) = dx;
    at(1) = dy;
  }

};

template <class Coord>
inline const Coord& dx(const vector_<2,Coord>& v) { return v[0]; }

template <class Coord>
inline const Coord& dy(const vector_<2,Coord>& v) { return v[1]; }

template <class Coord>
inline const Coord&
set_dx(vector_<2,Coord>& v, const Coord& val) {
    return v[0] = val;
}

template <class Coord>
inline const Coord&
set_dy(vector_<2,Coord>& v, const Coord& val) {
    return v[1] = val;
}

} // namespace infovis

#endif // INFOVIS_DRAWING_POINT_VEC2D_HPP
