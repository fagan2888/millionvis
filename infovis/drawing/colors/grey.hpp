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
#ifndef INFOVIS_DRAWING_COLORS_GREY_HPP
#define INFOVIS_DRAWING_COLORS_GREY_HPP

#include <infovis/drawing/color.hpp>

namespace infovis {

/**
 * Grey color space.
 */
struct color_space_grey {
  enum channel_name { grey, last_channel };
  static const char * name() { return "grey"; }
};

/**
 * Grey color type.
 */
struct color_grey : public color_type<float, color_space_grey>
{
  typedef color_type<float, color_space_grey> super;
  color_grey() {
    channel[grey] = 1.0f;
  }
  explicit color_grey(float val) : super(val) { }
  color_grey(const color_grey& other) : super(other.begin(), other.end()) { }
};

void convert(color_rgb<float>& rgb, const color_grey& grey);
void convert(color_grey& grey, const color_rgb<float>& rgb);

} // namespace infovis

#endif // INFOVIS_DRAWING_COLORS_GREY_HPP
