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
#include <infovis/drawing/inter/InteractorIdle.hpp>

namespace infovis {

bool
InteractorIdle::idle(const Event& ev)
{
  if (idle_) return false;
  if (doIdle(ev))
    idle_ = true;
  else
    idle_ = false;
  return idle_;
}

void
InteractorIdle::active(const Event& ev)
{
  if (! idle_) return;
  idle_ = false;
  doActive(ev);
}

bool
InteractorIdle::isIdle() const
{
  return idle_;
}

bool
InteractorIdle::doIdle(const Event&)
{
  return true;
}

void
InteractorIdle::doActive(const Event&)
{ }

} // namespace infovis
