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
#ifndef INFOVIS_DRAWING_INTERACTOR_DEFAULTMANAGERIDLE_HPP
#define INFOVIS_DRAWING_INTERACTOR_DEFAULTMANAGERIDLE_HPP

#include <infovis/drawing/inter/ManagerIdle.hpp>
#include <infovis/drawing/inter/MouseHandler.hpp>
#include <infovis/drawing/inter/TimerHandler.hpp>

namespace infovis {

class Interactor3States;

/**
 * Default implementation of Idle manager
 */
class DefaultManagerIdle : public ManagerIdle,
			   public MouseHandler,
			   public TimerHandler
{
public:
  DefaultManagerIdle();

  virtual void motion(float x, float y);
  virtual void timer();

  // InteractorManager
  virtual void connect(LiteWindow *);
  virtual void disconnect(LiteWindow *);

  void setTimeout(unsigned long millis) { timeout_ = millis; }
  unsigned long getTimeout() { return timeout_; }

  Interactor3States * getInteractor3States() const { return interactor3states_; }
  void setInteractor3States(Interactor3States * i) { interactor3states_ = i; }
  bool inhibit() const;
protected:
  unsigned long timeout_;
  int received_;
  Interactor3States * interactor3states_;
};

} // namespace infovis

#endif // INFOVIS_DRAWING_INTERACTOR_DEFAULTMANAGERIDLE_HPP
