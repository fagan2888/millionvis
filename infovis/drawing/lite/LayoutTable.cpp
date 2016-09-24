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
#include <infovis/drawing/lite/LayoutTable.hpp>
#include <algorithm>

namespace infovis {

LayoutTable::LayoutTable(int columns, float hgap, float vgap)
  : columns_(columns), hgap_(hgap), vgap_(vgap)
{ }

LayoutTable::~LayoutTable()
{ }

Box
LayoutTable::doLayoutIn(Lite * container)
{
  int i;
  int rows_ = (lite_.size() + columns_-1) / columns_;

  std::vector<float> columns(columns_, 0.0f);
  std::vector<float> rows(rows_, 0.0f);
  for (i = 0; i < lite_.size(); i++) {
    Vector v(extent(lite_[i]->getMinBounds()));

    if (dx(v) > columns[i % columns_])
      columns[i % columns_] = dx(v);
    if (dy(v) > rows[i / columns_])
      rows[i / columns_] = dy(v);
  }

  Box bounds(container->getBounds());
  std::vector<float> c_start(columns_+1);
  c_start[0] = xmin(bounds);
  for (i = 0; i < columns_; i++) {
    c_start[i+1] = c_start[i] + columns[i] + hgap_;
  }

  std::vector<float> r_start(rows_+1);
  r_start[0] = ymin(bounds);
  for (i = 0; i < rows_; i++) {
    r_start[i+1] = r_start[i] + rows[i] + vgap_;
  }

  for (i = 0; i < lite_.size(); i++) {
    Lite * l = lite_[i];
    int c = i % columns_;
    int r = i / columns_;
    l->setPosition(Point(c_start[c], r_start[r])); // move everything
    l->setBounds(Box(c_start[c], // give more room
		     r_start[r],
		     c_start[c] + columns[c],
		     r_start[r] + rows[r]));
  }
  return Box(min(bounds), Point(c_start[columns_]-hgap_,
				r_start[rows_]-vgap_));
}

} // namespace infovis
