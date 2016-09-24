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
#include <infovis/drawing/lite/LabelLayoutSimple.hpp>

namespace infovis {

LabelLayoutSimple::LabelLayoutSimple(const Box& box)
  : LabelLayout(box) 
{ }

LabelLayout::LayoutResult
LabelLayoutSimple::doLayout()
{
  for (List::const_iterator i = list_.begin(); i != list_.end(); i++) {
    LiteDisplacedLabel * lb = *i;
    Box b(lb->getBounds());

    if (! contains(bounds_, b)) {
      float dx = 0;
      float dy = 0;
      if (xmin(b) < xmin(bounds_)) {
	dx = xmin(bounds_) - xmin(b);
      }
      else if (xmax(b) > xmax(bounds_)) {
	dx = xmax(bounds_) - xmax(b);
      }
      if (ymin(b) < ymin(bounds_)) {
	dy = ymin(bounds_) - ymin(b);
      }
      else if (ymax(b) > ymax(bounds_)) {
	dy = ymax(bounds_) - ymax(b);
      }
      lb->movePosition(Vector(dx, dy));
    }
  }
  return layout_dont_overlap;
}

} // namespace infovis
