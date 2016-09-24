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
#include <infovis/drawing/Transform.hpp>
#include <infovis/drawing/gl.hpp>
#include <cmath>

namespace infovis {
  void
  Transform::translate(const Vector& v)
  {
    oplist.push_back(op_trans);
    paramlist.push_back(dx(v));
    paramlist.push_back(dy(v));
  }
  void
  Transform::scale(const Vector& v)
  {
    oplist.push_back(op_scale);
    paramlist.push_back(dx(v));
    paramlist.push_back(dy(v));
  }
  void
  Transform::rotate(float a)
  {
    oplist.push_back(op_rotate);
    paramlist.push_back(a);
  }
  void
  Transform::matrix(const Matrix& mat)
  {
    oplist.push_back(op_matrix);
    paramlist.insert(paramlist.end(),
		     mat.m, mat.m+6);
  }
  void
  Transform::matrix(float sxx, float sxy, float syx, float syy,
		    float tx, float ty)
  {
    oplist.push_back(op_matrix);
    paramlist.push_back(sxx);
    paramlist.push_back(sxy);
    paramlist.push_back(syx);
    paramlist.push_back(syy);
    paramlist.push_back(tx);
    paramlist.push_back(ty);
  }
  void
  Transform::apply() const
  {
    ParamList::const_iterator p = paramlist.begin();
    for (OpList::const_iterator o = oplist.begin();
	 o != oplist.end(); o++) {
      switch(*o) {
      case op_trans: {
	float dx = *p++;
	float dy = *p++;
	gl::translate(dx, dy);
	break;
      }
      case op_scale: {
	float dx = *p++;
	float dy = *p++;
	gl::scale(dx, dy);
	break;
      }
      case op_rotate: {
	float angle = *p++;
	gl::rotate(angle, 0, 0, 1);
	break;
      }
      case op_matrix: {
	GLfloat m[16];
	m[0] = *p++;
	m[1] = *p++;
	m[2] = 0;
	m[3] = 0;
	m[4] = *p++;
	m[5] = *p++;
	m[6] = 0;
	m[7] = 0;
	m[8] = 0;
	m[9] = 0;
	m[10] = 1;
	m[11] = 0;
	m[12] = *p++;
	m[13] = *p++;
	m[14] = 0;
	m[15] = 0;
	gl::multmatrix(m);
	break;
      }
      }
    }
  }
  void
  Transform::apply(Matrix& mat) const
  {
    ParamList::const_iterator p = paramlist.begin();
    for (OpList::const_iterator o = oplist.begin();
	 o != oplist.end(); o++) {
      switch(*o) {
      case op_trans: {
	Matrix m;
	m[4] = *p++;
	m[5] = *p++;
	mat = mat * m;
	break;
      }
      case op_scale: {
	Matrix m;
	m[0] = *p++;
	m[1] = *p++;
	mat = mat * m;
	break;
      }
      case op_rotate: {
	float angle = *p++;
	angle *= 3.14159265358979323846f / 180.0f;
	Matrix m;
	double s = sin(angle);
	double c = cos(angle);
	m[0] = c;
	m[1] = s;
	m[2] = -s;
	m[3] = c;
	mat = mat * m;
	break;
      }
      case op_matrix: {
	Matrix m(p);
	mat = mat * m;
	p += 6;
	break;
      }
      }
    }
  }

} // namespace infovis
