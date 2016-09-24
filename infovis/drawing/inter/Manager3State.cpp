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
#include <infovis/drawing/inter/Manager3State.hpp>
#include <infovis/drawing/inter/Interactor3States.hpp>

namespace infovis {

Manager3State::Manager3State()
  : inter_(0)
{
  initFieldEvent(event_);
}

void
Manager3State::initFieldEvent(Event& ev)
{
  ev.clear();
  ev.addField(new FieldFloat(field_x));
  ev.addField(new FieldFloat(field_y));
  ev.addField(new FieldInt(field_mod));
}

const string&
Manager3State::interactorName() const
{
  return getInteractorName();
}

void
Manager3State::doDesactivate(const Event& ev)
{
  if (inter_ != 0) {
    inter_->desactivate(ev);
    inter_ = 0;
  }
}

void
Manager3State::doAbort(const Event& ev)
{
  if (inter_ != 0) {
    inter_->abort(ev);
    inter_ = 0;
  }
}

void
Manager3State::doProximityIn(const Event& ev)
{
  if (inter_ == 0)
    inter_ = dynamic_cast<Interactor3States*>(pick(ev));
  if (inter_ != 0) {
    inter_->proximity_in(ev);
  }
}

void
Manager3State::doProximityOut(const Event& ev)
{
  if (inter_ != 0)
    inter_->proximity_out(ev);
}

void
Manager3State::doMove(const Event& ev)
{
  if (inter_ != 0)
    inter_->move(ev);
}

bool
Manager3State::doStart(const Event& ev)
{
  if (inter_ == 0)
    inter_ = dynamic_cast<Interactor3States*>(pick(ev));
  if (inter_ != 0)
    return inter_->start(ev);
  return false;
}

void
Manager3State::doDrag(const Event& ev)
{
  if (inter_ != 0)
    inter_->drag(ev);
}

void
Manager3State::doFinish(const Event& ev)
{
  if (inter_ != 0) {
    inter_->finish(ev);
    inter_ = 0;
  }
}

} // namespace infovis
