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
#include <infovis/drawing/inter/InteractorManager.hpp>

namespace infovis {

InteractorManager::InteractorManager()
  : window_(0),
    event_("event")
{ }

InteractorManager::~InteractorManager()
{ }
  
void
InteractorManager::connect(LiteWindow * win)
{
  window_ = win;
}

void
InteractorManager::disconnect(LiteWindow * win)
{
  window_ = 0;
}

Interactor *
InteractorManager::pick(const Event& ev)
{
  if (window_ == 0)
    return 0;
  Interactor * inter = 0;
  if (! ev.hasField(field_x) || ! ev.hasField(field_y))
    return 0;

  float x = getFieldX(ev);
  float y = getFieldY(ev);
  const string& iname = interactorName();
  Pick pick;

  window_->pick(Box(x-1, y-1, x+1, y+1), pick);

  for (Pick::reverse_iterator i = pick.rbegin(); i != pick.rend(); i++) {
    inter = (*i)->interactor(iname, mouse_id);
    if (inter != 0) {
      break;
    }
  }
  return inter;
}

LiteWindow *
InteractorManager::getWindow() const
{
  return window_;
}


} // namespace infovis 
