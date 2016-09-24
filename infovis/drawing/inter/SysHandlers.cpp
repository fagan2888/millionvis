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
#include <infovis/drawing/inter/SysHandlers.hpp>

namespace infovis {

SystemMouseHandler::SystemMouseHandler()
  : Manager3State()
{ }

void
SystemMouseHandler::button(int button, bool down, float x, float y)
{
  if (button == 0) {
    event_.nextGlobalTimeStamp();
    setFieldX(event_, x);
    setFieldY(event_, y);
    setFieldMod(event_, window_->getModifiers());
    
    if (down)
      start(event_);
    else
      finish(event_);
  }
}

void
SystemMouseHandler::motion(float x, float y)
{
  event_.nextGlobalTimeStamp();
  setFieldX(event_, x);
  setFieldY(event_, y);
  setFieldMod(event_, window_->getModifiers());
  if (isDragged())
    drag(event_);
  else
    move(event_);
}

void
SystemMouseHandler::connect(LiteWindow * win)
{
  Manager3State::connect(win);
  win->addMouseHandler(this);
}

void
SystemMouseHandler::disconnect(LiteWindow * win)
{
  win->removeMouseHandler(this);
  Manager3State::disconnect(win);
}


SystemEnterLeaveHandler::SystemEnterLeaveHandler()
{ }

void
SystemEnterLeaveHandler::motion(float x, float y)
{
  event_.nextGlobalTimeStamp();
  setFieldX(event_, x);
  setFieldY(event_, y);
  setFieldMod(event_, window_->getModifiers());
  move(event_);
}

void
SystemEnterLeaveHandler::connect(LiteWindow * win)
{
  ManagerEnterLeave::connect(win);
  win->addMouseHandler(this);
}

void
SystemEnterLeaveHandler::disconnect(LiteWindow * win)
{
  win->removeMouseHandler(this);
  ManagerEnterLeave::disconnect(win);
}

} // namespace infovis
