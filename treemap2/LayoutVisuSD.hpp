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
#ifndef TREEMAP2_LAYOUTVISUSD_HPP
#define TREEMAP2_LAYOUTVISUSD_HPP

#include <infovis/tree/treemap/slice_and_dice.hpp>

#include <LiteTreemap.hpp>
#include <LayoutVisu.hpp>
#include <BoxDrawer.hpp>

namespace infovis {

typedef weight_interpolator<WeightMap> Interp;

class LayoutVisuSliceAndDice : public LayoutVisu
{
public:
  LayoutVisuSliceAndDice(LiteTreemap * tm);
  virtual unsigned draw(float param);
  virtual unsigned pick(float param);
  virtual void boxlist(float param, AnimateTree::BoxList& bl, int depth);
};
} // namespace infovis

#endif // TREEMAP2_LAYOUTVISUSD_HPP
