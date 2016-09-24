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
#include <infovis/drawing/colors/grey.hpp>

namespace infovis {

void convert(color_rgb<float>& rgb, const color_grey& grey)
{
  typedef color_rgb<float> Color;

  for (int chan = 0; chan < Color::last_channel; chan++)
    rgb[chan] = grey[0];
}

void convert(color_grey& grey, const color_rgb<float>& rgb)
{
  typedef color_rgb<float> Color;

  grey[0] =
    0.299f * rgb[Color::red] +
    0.587f * rgb[Color::green] +
    0.114f * rgb[Color::blue];
}
} // namespace infovis
