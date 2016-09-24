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
#include <LiteRangeSliderGraph.hpp>
#include <infovis/drawing/gl_support.hpp>

namespace infovis {

LiteRangeSliderGraph::LiteRangeSliderGraph(BoundedRangeObservable * observable,
					   const Box& bounds,
					   const BarGraph * bar,
					   direction dir,
					   const Color& fg,
					   const Color& bg,
					   Font * font,
					   float minmax_size
					   )
  : LiteRangeSlider(observable, bounds, dir, fg, bg, font, minmax_size),
    bar_(bar)
{ }

LiteRangeSliderGraph::LiteRangeSliderGraph(const Box& bounds,
					   const BarGraph * bar,
					   direction dir,
					   const Color& fg,
					   const Color& bg,
					   Font * font,
					   float minmax_size
					   )
  : LiteRangeSlider(bounds, dir, fg, bg, font, minmax_size),
    bar_(bar)
{ }
  
Lite *
LiteRangeSliderGraph::clone() const
{
  return new LiteRangeSliderGraph(getObservable(),
				  getBounds(),
				  bar_,
				  getDirection(),
				  getForegroundColor(),
				  getBackgroundColor(),
				  getFont(),
				  min_size_);
}

void
LiteRangeSliderGraph::renderOverlay(const Box& b)
{
  glPushAttrib(GL_COLOR_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  LiteRangeSlider::renderOverlay(b);
  Box inner(xmin(b)+getMinSize(), ymin(b),
	    xmax(b)-getMaxSize(), ymax(b));
  set_color(Color(0,1.0,0, 0.7));
  bar_->render(inner, direction_);
  glPopAttrib();
}


} // namespace infovis
