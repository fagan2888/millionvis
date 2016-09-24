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
#include <treemap2/ColorRamp.hpp>
//#include <infovis/drawing/colors/hvc.hpp>
#define BREWER_COLORS

namespace infovis {


static const ColorRamp&
_ramp_categorical1()
{
  static ColorRamp ramp;
  if (ramp.empty()) {
    ramp.push_back(Color(228U,26U,28U));
    ramp.push_back(Color(55U,126U,184U));
    ramp.push_back(Color(77U,175U,74U));
    ramp.push_back(Color(152U,78U,163U));
    ramp.push_back(Color(255U,127U,0U));
    ramp.push_back(Color(255U,255U,51U));
    ramp.push_back(Color(166U,86U,40U));
    ramp.push_back(Color(247U,129U,191U));
  }
  return ramp;
}

static const ColorRamp&
_ramp_categorical2()
{
  static ColorRamp ramp;
  if (ramp.empty()) {
    ramp.push_back(color_half_grey);
    ramp.push_back(color_white);
    ramp.push_back(color_red);
    ramp.push_back(color_green);
    ramp.push_back(color_blue);
    ramp.push_back(color_cyan);
    ramp.push_back(color_magenta);
    ramp.push_back(color_yellow);
  }
  return ramp;
}


static const ColorRamp&
_ramp_sequential1()
{
  static ColorRamp ramp;
  if (ramp.empty()) {
#ifdef BREWER_COLORS
    ramp.push_back(Color(255U,247U,251U));
    ramp.push_back(Color(3U,78U,123U));
#else
    ramp.push_back(color_blue);
    ramp.push_back(color_red);
#endif
  }
  return ramp;
}

static const ColorRamp&
_ramp_sequential2()
{
  static ColorRamp ramp;
  if (ramp.empty()) {
#ifdef BREWER_COLORS
    ramp.push_back(Color(255U,255U,229U));
    ramp.push_back(Color(140U,051U,005U));
#else
    ramp.push_back(color_red);
    ramp.push_back(color_green);
#endif
  }
  return ramp;
}

const ColorRamp&
getRamp(Ramp r)
{
  switch(r) {
  case ramp_categorical1:
    return _ramp_categorical1();
  case ramp_categorical2:
    return _ramp_categorical2();
  case ramp_sequential1:
    return _ramp_sequential1();
  case ramp_sequential2:
    return _ramp_sequential2();
  }
  return _ramp_sequential1();
}

} // namespace infovis
