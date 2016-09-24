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
#include <infovis/drawing/lite/LiteButton.hpp>

namespace infovis {

LiteButton::LiteButton(Lite * child)
  : LiteProxy(child)
{ }

Interactor *
LiteButton::interactor(const string& name, int tool_id)
{
  if (isA(name) && tool_id == mouse_id) {
    return this;
  }
  return 0;
}

Lite *
LiteButton::clone() const
{
  return new LiteButton(lite_->clone());
}

void
LiteButton::doFinish(const Event& ev)
{
  if (infovis::inside(getBounds(), getFieldX(ev), getFieldY(ev))) {
    notifyChanged();
  }
  repaint();
}

} // namespace infovis
