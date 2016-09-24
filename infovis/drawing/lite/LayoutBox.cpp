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
#include <infovis/drawing/lite/LayoutBox.hpp>
#include <algorithm>

namespace infovis {

LayoutBox::LayoutBox(Direction dir, float gap)
  : dir_(dir), gap_(gap) { }
LayoutBox::~LayoutBox() { }

Layout *
LayoutBox::clone() const
{
  return new LayoutBox(dir_);	// don't copy contents
}

Box
LayoutBox::doLayoutIn(Lite * container)
{
  Vector size(0, 0);

  Box b(container->getBounds());
  Point p(min(b));
  for (Lite::List::const_iterator i = lite_.begin();
       i != lite_.end(); i++) {
    Lite * l = *i;
    Box b(l->getBounds());
    Vector v(extent(b));

    l->movePosition(p-min(b));
    if (dir_ == horizontal) {
      set_dx(size, dx(size)+gap_+dx(v));
      set_dy(size, std::max(dy(size),dy(v)));
      set_x(p, x(p)+gap_+dx(v));
    }
    else {
      set_dx(size, std::max(dx(size),dx(v)));
      set_dy(size, dy(size)+gap_+dy(v));
      set_y(p, y(p)+gap_+dy(v));
    }
  }
  container->setSize(size);
  return Box(min(b),size);
}

} // namespace infovis
