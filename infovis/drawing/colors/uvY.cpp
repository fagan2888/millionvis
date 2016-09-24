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
#include <infovis/drawing/colors/uvY.hpp>

namespace infovis {

color_uvY::color_uvY()
{
  color_xyz white;

  float div =
    white[color_xyz::x] +
    white[color_xyz::y] * 15.0f +
    white[color_xyz::z] * 3.0f;

  channel[u_prime] = 4.0f * white[color_xyz::x] / div;
  channel[v_prime] = 9.0f * white[color_xyz::y] / div;
  channel[Y] = white[color_xyz::y];
}

void convert(color_xyz& xyz, const color_uvY& uvY)
{
  typedef color_xyz To;
  typedef color_uvY From;

  double div, Y;

  Y = uvY[From::Y];
  div = 6.0 * uvY[From::u_prime] - 16.0 * uvY[From::v_prime] + 12.0;
  if (div == 0.0) {
    xyz = color_xyz(0);
  }
  else {
    xyz[To::x] = 9.0 * uvY[From::u_prime] / div;
    xyz[To::y] = 4.0 * uvY[From::v_prime] / div;
    xyz[To::z] = (-3.0 * uvY[From::u_prime] -
		  20.0 * uvY[From::v_prime] +
		  12.0) / div;
  }
}

void convert(color_uvY& uvY, const color_xyz& xyz)
{
  typedef color_xyz From;
  typedef color_uvY To;

  float div = xyz[From::x] + 15.0*xyz[From::y] + 3*xyz[From::z];

  if (div == 0) {
    uvY = color_uvY();
  } else {
    uvY[To::u_prime] = 4.0 * xyz[From::x] / div;
    uvY[To::v_prime] = 9.0 * xyz[From::x] / div;
    uvY[To::Y] = xyz[From::y];    
  }
}


} // namespace infovis
