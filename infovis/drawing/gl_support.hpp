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
#ifndef INFOVIS_DRAWING_GL_SUPPORT_HPP
#define INFOVIS_DRAWING_GL_SUPPORT_HPP

#include <infovis/drawing/box.hpp>
#include <infovis/drawing/color.hpp>
#include <infovis/drawing/gl.hpp>

namespace infovis {

// guess this one
inline int type_of(char) { return GL_BYTE; }
inline int type_of(unsigned char) { return GL_UNSIGNED_BYTE; }
inline int type_of(short) { return GL_SHORT; }
inline int type_of(unsigned short) { return GL_UNSIGNED_SHORT; }
inline int type_of(int) { return GL_INT; }
inline int type_of(unsigned int) { return GL_UNSIGNED_INT; }
inline int type_of(float) { return GL_FLOAT; }
inline int type_of(double) { return GL_DOUBLE; }
  
template <class Box>
void draw_box(const Box& b)
{
  gl::rect(xmin(b), ymin(b), xmax(b), ymax(b));
}

template <class Box>
void stroke_box(const Box& b)
{
  gl::begin_line_loop l;
  gl::vertex(xmin(b), ymin(b));
  gl::vertex(xmax(b), ymin(b));
  gl::vertex(xmax(b), ymax(b));
  gl::vertex(xmin(b), ymax(b));
}

template <class Color>
void set_color(const Color& c, color_space_rgb)
{
  gl::color(c[0], c[1], c[2]);
}

template <class Color>
void set_color(const Color& c, color_space_rgba)
{
  gl::color(c[0], c[1], c[2], c[3]);
}

#if 0
template <class Color, class S>
void set_color(const Color& c, S)
{
  color_rgba rgba(c);
  color(rgba[0], rgba[1], rgba[2], rgba[3]);
}
#endif

template <class Color>
void set_color(const Color& c)
{
  set_color(c, color_space_traits<Color>::color_space());
}

template <class Coord>
void set_vertex(const point_<2, Coord>& p)
{
  gl::vertex(x(p), y(p));
}
} // namespace infovis

#endif // INFOVIS_DRAWING_GL_SUPPORT_HPP
