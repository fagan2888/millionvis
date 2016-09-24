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
#include <infovis/drawing/inter/Interactor3States.hpp>

namespace infovis {

void
Interactor3States::proximity_in(const Event& ev)
{
  if (state != state_away) return;
  doProximityIn(ev);
  state = state_present;
}

void
Interactor3States::proximity_out(const Event& ev)
{
  if (state != state_present) return;
  doProximityOut(ev);
  state = state_away;
}

void
Interactor3States::move(const Event& ev)
{
  if (state != state_present) return;
  doMove(ev);
}

bool
Interactor3States::start(const Event& ev)
{
  if (state != state_present) return false;
  if (doStart(ev)) {
    state = state_dragged;
    start_pos = Point(getFieldX(ev),getFieldY(ev));
    return true;
  }
  else
    return false;
}

void
Interactor3States::drag(const Event& ev)
{
  if (state != state_dragged) return;
  doDrag(ev);
  current_pos = Point(getFieldX(ev),getFieldY(ev));
}

void
Interactor3States::finish(const Event& ev)
{
  if (state != state_dragged) return;
  doFinish(ev);
  state = state_present;
  current_pos = Point(getFieldX(ev),getFieldY(ev));
}

void
Interactor3States::desactivate(const Event& ev)
{
  Interactor::desactivate(ev);
}

void
Interactor3States::abort(const Event& ev)
{
  state = state_present;
  Interactor::abort(ev);
}

void
Interactor3States::doProximityIn(const Event& ev) { }
void
Interactor3States::doProximityOut(const Event& ev) { }
void
Interactor3States::doMove(const Event& ev) { }
bool
Interactor3States::doStart(const Event& ev) { return true; }
void
Interactor3States::doDrag(const Event& ev) { }
void
Interactor3States::doFinish(const Event& ev) { }
} // namespace infovis

