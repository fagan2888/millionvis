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
#include <infovis/drawing/colors/xyz.hpp>

namespace infovis {

color_xyz::color_xyz()
{
  channel[x] = float(0.38106149108714790+0.32025712365352110+0.24834578525933100);
  channel[y] = float(0.20729745115140850+0.68054638776373240+0.11215616108485920);
  channel[z] = float(0.02133944350088028+0.14297193020246480+1.24172892629665500);
}

void
convert(color_rgb<float>& rgb, const color_xyz& xyz)
{
  rgb[0] = (xyz[0] * 3.48340481253539000f +
	    xyz[1] * -1.52176374927285200f +
	    xyz[2] * -0.55923133354049780f);
  rgb[1] = (xyz[0] * -1.07152751306193600f +
	    xyz[1] * 1.96593795204372400f +
	    xyz[2] * 0.03673691339553462f);
  rgb[2] = (xyz[0] * 0.06351179790497788f +
	    xyz[1] * -0.20020501000496480f +
	    xyz[2] * 0.81070942031648220f);
}

void
convert(color_xyz& xyz, const color_rgb<float>& rgb)
{
  xyz[0] = (rgb[0] * 0.38106149108714790f +
	    rgb[1] * 0.32025712365352110f +
	    rgb[2] * 0.24834578525933100f);
  xyz[1] = (rgb[0] * 0.20729745115140850f +
	    rgb[1] * 0.68054638776373240f +
	    rgb[2] * 0.11215616108485920f);
  xyz[2] = (rgb[0] * 0.02133944350088028f +
	    rgb[1] * 0.14297193020246480f +
	    rgb[2] * 1.24172892629665500f);
}


} // namespace infovis
