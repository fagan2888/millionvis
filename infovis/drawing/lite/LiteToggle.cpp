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
#include <infovis/drawing/lite/LiteToggle.hpp>

namespace infovis {

LiteToggle::LiteToggle(Lite * on, Lite * off)
  : LiteSwitch()
{
  addChild(on);
  addChild(off);
  setSelected(0);
}

Lite *
LiteToggle::clone() const
{
  return new LiteToggle(getChild(0)->clone(),
			getChild(1)->clone());
}

void
LiteToggle::toggle()
{
  setSelected(getSelected() == 0 ? 1 : 0);
  notifyChanged();
}

bool
LiteToggle::isOn() const
{
  return getSelected() == 0;
}

} // namespace infovis
