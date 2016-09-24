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
#include <infovis/drawing/inter/ManagerIdle.hpp>
#include <infovis/drawing/inter/InteractorIdle.hpp>

namespace infovis {

ManagerIdle::ManagerIdle()
  : inter_(0)
{
  initFieldEvent(event_);
}

void
ManagerIdle::initFieldEvent(Event& ev)
{
  ev.clear();
  ev.addField(new FieldFloat(field_x));
  ev.addField(new FieldFloat(field_y));
  ev.addField(new FieldInt(field_mod));
}

const string&
ManagerIdle::interactorName() const
{
  return getInteractorName();
}

void
ManagerIdle::doDesactivate(const Event& ev)
{
  if (inter_ != 0) {
    inter_->desactivate(ev);
    inter_ = 0;
  }
}

void
ManagerIdle::doAbort(const Event& ev)
{
  if (inter_ != 0) {
    inter_->abort(ev);
    inter_ = 0;
  }
}

bool
ManagerIdle::doIdle(const Event& ev)
{
  inter_ = dynamic_cast<InteractorIdle*>(pick(ev));

  if (inter_ == 0) return false;
  if (inter_->idle(ev))
    return true;
  inter_ = 0;
  return false;
}

void
ManagerIdle::doActive(const Event& ev)
{
  if (inter_ == 0) return;
  inter_->active(ev);
  desactivate(ev);
}

} // namespace infovis
