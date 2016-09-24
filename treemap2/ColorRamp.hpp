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
#ifndef TREEMAP2_COLORRAMP_HPP
#define TREEMAP2_COLORRAMP_HPP

#include <infovis/drawing/drawing.hpp>
#include <vector>

namespace infovis {

typedef std::vector<Color> ColorRamp;

enum Ramp {
#if 1
  ramp_categorical1,
  ramp_categorical2,
  ramp_sequential1,
  ramp_sequential2,
#else
  ramp_binary,
  ramp_qualitative,
  ramp_sequential,
  ramp_diverging,
#endif
  ramp_max
};

const ColorRamp& getRamp(Ramp r);


} // namespace infovis

#endif // TREEMAP2_COLORRAMP_HPP
