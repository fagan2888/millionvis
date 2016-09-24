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
#ifndef INFOVIS_DRAWING_INTERACTOR_SYSHANDLERS_HPP
#define INFOVIS_DRAWING_INTERACTOR_SYSHANDLERS_HPP

#include <infovis/drawing/inter/MouseHandler.hpp>
#include <infovis/drawing/inter/KeyboardHandler.hpp>
#include <infovis/drawing/inter/Manager3State.hpp>
#include <infovis/drawing/inter/ManagerEnterLeave.hpp>

namespace infovis {

/**
 * The system mouse handler
 */
class SystemMouseHandler : public MouseHandler,
			   public Manager3State
{
public:
  SystemMouseHandler();
  virtual void button(int button, bool down, float x, float y);
  virtual void motion(float x, float y);
  virtual void connect(LiteWindow *);
  virtual void disconnect(LiteWindow *);
};

/**
 * The system EnterLeave handler
 */ 
class SystemEnterLeaveHandler : public MouseHandler,
				public ManagerEnterLeave
{
public:
  SystemEnterLeaveHandler();
  virtual void motion(float x, float y);
  virtual void connect(LiteWindow *);
  virtual void disconnect(LiteWindow *);
};

#if 0
class SystemKeyboardHandler : public KeyboardHandler,
			      public ManagerKeyboard
{
};
#endif

} // namespace infovis

#endif // INFOVIS_DRAWING_INTERACTOR_SYSHANDLERS_HPP
