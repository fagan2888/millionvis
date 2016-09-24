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
#include <infovis/drawing/lite/LiteEnterLeaveShape.hpp>

namespace infovis {

LiteEnterLeaveShape::LiteEnterLeaveShape(LiteShape * l, const Color& in, const Color& out)
  : LiteEnterLeave(l),
    shape_(l),
    in_(in),
    out_(out)
{
}

Lite *
LiteEnterLeaveShape::clone() const
{
  return new LiteEnterLeaveShape(dynamic_cast<LiteShape*>(shape_->clone()), in_, out_);
}

bool
LiteEnterLeaveShape::doEnter(const Event& )
{
  shape_->setColor(in_);
  repaint();
  return true;
}

void
LiteEnterLeaveShape::doLeave(const Event& )
{
  shape_->setColor(out_);
  repaint();
}
} // namespace infovis
