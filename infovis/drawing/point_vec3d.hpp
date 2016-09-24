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
#ifndef INFOVIS_DRAWING_POINT_VEC3D_HPP
#define INFOVIS_DRAWING_POINT_VEC3D_HPP

#include <infovis/drawing/poit_vec.hpp>

namespace infovis {

/**
 * Point in 3D template
 */
template <class Coord>
struct point3d : point_<3, Coord>
{
  typedef point_<3, Coord> super;

  point3d() { }

  point3d(const point3d& p) : point_<3, Coord>(p) { }

  template <class Coord3>
  point3d(const point_<3, Coord3>& p) : super(p) {}

  template <class Coord3>
  explicit point3d(const vector_<2,Coord3>& v) {
    at(0) = v[0];
    at(1) = v[1];
    at(2) = Coord(0);
  }

#ifndef __GNUG__
  template <class Coord3>
  explicit point3d(const vector_<3,Coord3>& v) : super(v) {}
#endif

  point3d(const Coord& x, const Coord& y, const Coord& z = Coord(0)) {
    at(0) = x;
    at(1) = y;
    at(2) = z;
  }

};

template <class Coord>
inline const Coord&
x(const point_<3, Coord>& p) { return p[0]; }

template <class Coord>
inline const Coord&
y(const point_<3, Coord>& p) { return p[1]; }

template <class Coord>
inline const Coord&
z(const point_<3, Coord>& p) { return p[2]; }

template <class Coord>
inline const Coord&
set_x(point_<3, Coord>& p, const Coord& v) {
  return p[0] = v;
}

template <class Coord>
inline const Coord&
set_y(point_<3, Coord>& p, const Coord& v) {
  return p[1] = v;
}

template <class Coord>
inline const Coord&
set_z(point_<3, Coord>& p, const Coord& v) {
  return p[2] = v;
}

/**
 * Vector in 3D template
 */
template <class Coord>
struct vector3d : vector_<3, Coord>
{
  typedef vector_<3, Coord> super;

  vector3d () { }

  vector3d(const vector3d& v) : super(v) {}

  template <class Coord3>
  vector3d(const vector_<3, Coord3> & v) : super(v) {}

  template <class Coord3>
  explicit vector3d(const point_<2,Coord3>& p) {
    at(0) = p[0];
    at(1) = p[1];
    at(2) = Coord(0);
  }

#ifndef __GNUG__
  template <class Coord3>
  explicit vector3d(const point_<3,Coord3>& p) : super(p) {}
#endif

  vector3d(const Coord& dx, const Coord& dy, const Coord& dz = Coord(0)) {
    at(0) = dx;
    at(1) = dy;
    at(1) = dz;
  }

};

template <class Coord>
inline const Coord& dx(const vector_<3,Coord>& v) { return v[0]; }

template <class Coord>
inline const Coord& dy(const vector_<3,Coord>& v) { return v[1]; }

template <class Coord>
inline const Coord& dz(const vector_<3,Coord>& v) { return v[2]; }

template <class Coord>
inline const Coord&
set_dx(vector_<3,Coord>& v, const Coord& val) {
    return v[0] = val;
}

template <class Coord>
inline const Coord&
set_dy(vector_<3,Coord>& v, const Coord& val) {
    return v[1] = val;
}

template <class Coord>
inline const Coord&
set_dz(vector_<3,Coord>& v, const Coord& val) {
    return v[2] = val;
}

} // namespace infovis

#endif // INFOVIS_DRAWING_POINT_VEC3D_HPP
