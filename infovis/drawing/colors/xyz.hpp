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
#ifndef INFOVIS_DRAWING_COLORS_XXY_HPP
#define INFOVIS_DRAWING_COLORS_XYZ_HPP

#include <infovis/drawing/color.hpp>

namespace infovis {

struct color_space_xyz {
  enum channel_name { x, y, z, last_channel };
  static const char * name() { return "xyz"; }
};

struct color_xyz : public color_type<float, color_space_xyz>
{
  typedef color_type<float, color_space_xyz> super;

  color_xyz();
  explicit color_xyz(float val) : super(val) {}
  color_xyz(const color_xyz& r) : super(r.begin(), r.end()) { }
  color_xyz(float X, float Y, float Z) {
    channel[x] = X;
    channel[y] = Y;
    channel[z] = Z;
  }
};

void convert(color_rgb<float>& rgb, const color_xyz& xyz);
void convert(color_xyz& xyz, const color_rgb<float>& rgb);


} // namespace infovis

#endif // INFOVIS_DRAWING_COLORS_XYZ_HPP
