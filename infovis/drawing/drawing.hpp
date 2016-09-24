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
#ifndef INFOVIS_DRAWING_BASE_HPP
#define INFOVIS_DRAWING_BASE_HPP

#include <infovis/alloc.hpp>
#include <infovis/drawing/point_vec2d.hpp>
#include <infovis/drawing/box.hpp>
#include <infovis/drawing/color.hpp>
#include <string>
using std::string;

namespace infovis {

typedef float Coord;
typedef point2d<Coord> Point;
typedef vector2d<Coord> Vector;
typedef box_min_max<Coord> Box;
typedef color_rgba<unsigned char> Color;
extern const Color color_none;
extern const Color color_white;
extern const Color color_black;
extern const Color color_red;
extern const Color color_green;
extern const Color color_blue;
extern const Color color_cyan;
extern const Color color_magenta;
extern const Color color_yellow;
extern const Color color_half_grey;

} // namespace infovis

#endif // INFOVIS_DRAWING_BASE_HPP
