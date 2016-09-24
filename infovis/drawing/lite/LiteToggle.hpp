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
#ifndef INFOVIS_DRAWING_LITETOGGLE_HPP
#define INFOVIS_DRAWING_LITETOGGLE_HPP

#include <infovis/drawing/lite/LiteSwitch.hpp>
#include <infovis/drawing/notifiers/Change.hpp>

namespace infovis {

/**
 * Lite component that toggles bewteen two states.
 */
class LiteToggle : public LiteSwitch,
		   public DefaultChangeObservable
{
public:
  LiteToggle(Lite * on, Lite * off);

  virtual Lite * clone() const;

  virtual void toggle();

  bool isOn() const;
};

} // namespace infovis


#endif // INFOVIS_DRAWING_LITETOGGLE_HPP
