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

#include <LiteTreemap.hpp>
#include <BoxDrawer.hpp>
#include <LayoutVisu.hpp>
#include <LayoutVisuSQ.hpp>
#include <LayoutVisuSD.hpp>
#include <LayoutVisuSP.hpp>

namespace infovis {

LayoutVisu::~LayoutVisu()
{ }

static LayoutVisuSquarified layout_squarified(0);
static LayoutVisuSliceAndDice layout_slice_and_dice(0);
static LayoutVisuScatterPlot layout_scatter_plot(0);

LayoutVisu *
LayoutVisu::create_visu(LiteTreemap::Layout l, LiteTreemap * tm)
{
  switch(l) {
  case LiteTreemap::layout_squarified:
  case LiteTreemap::layout_strip:
    layout_squarified.tm_ =  tm;
    return &layout_squarified;
  case LiteTreemap::layout_slice_and_dice:
    layout_slice_and_dice.tm_ =  tm;
    return &layout_slice_and_dice;
  case LiteTreemap::layout_scatter_plot:
    layout_scatter_plot.tm_ =  tm;
    return &layout_scatter_plot;
  default:
    break;
  }
  return 0;
}

};
