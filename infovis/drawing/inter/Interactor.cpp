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
#include <infovis/drawing/inter/Interactor.hpp>

namespace infovis {

Interactor::~Interactor() { }

bool
Interactor::activate(const Event& ev)
{
  if (state_ == state_active) return false;
  state_ = state_active;
  bool ret = doActivate(ev);
  return ret;
}

void
Interactor::desactivate(const Event& ev)
{
  if (state_ != state_active) return;
  state_ = state_inactive;
  doDesactivate(ev);
}

void
Interactor::abort(const Event& ev)
{
  if (state_ != state_active) return;
  state_ = state_inactive;
  doAbort(ev);
}

bool
Interactor::doActivate(const Event&) { return true; }

void
Interactor::doDesactivate(const Event&) { }

void
Interactor::doAbort(const Event&) { }

bool
Interactor::isA(const string& n) const
{
  return n == getInteractorName();
}

} // namespace infovis
