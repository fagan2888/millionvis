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
#ifndef INFOVIS_DRAWING_INTERACTOR_INTERACTOR_3STATE_HPP
#define INFOVIS_DRAWING_INTERACTOR_INTERACTOR_3STATE_HPP

#include <infovis/drawing/inter/Interactor.hpp>

namespace infovis {

/**
 * Base class for Interactor managing 3 States.
 */
class Interactor3States : public Interactor
{
public:
  enum State {
    state_away,
    state_present,
    state_dragged
  };

  Interactor3States()
    : Interactor("3States"), state(state_present) {}
  Interactor3States(const Interactor3States& other)
    : Interactor("3States"), state(state_present) { }

  void desactivate(const Event&);
  void abort(const Event&);

  void proximity_in(const Event& ev); // away->present
  void proximity_out(const Event& ev); // present->away
  void move(const Event& ev); // present->present
  bool start(const Event& ev); // present->dragged
  void drag(const Event& ev); // dragged->dragged
  void finish(const Event& ev); // dragged->present

  virtual void doProximityIn(const Event& ev);
  virtual void doProximityOut(const Event& ev);
  virtual void doMove(const Event& ev);
  virtual bool doStart(const Event& ev);
  virtual void doDrag(const Event& ev);
  virtual void doFinish(const Event& ev);

  State getState() const { return state; }
  bool isAway() const { return state == state_away; }
  bool isPresent() const { return state == state_present; }
  bool isDragged() const { return state == state_dragged; }

  const Point& getStartPos() const { return start_pos; }
  const Point& getCurPos() const { return current_pos; }
protected:
  State state;
  Point start_pos;
  Point current_pos;
};

} // namespace infovis

#endif // INFOVIS_DRAWING_INTERACTOR_INTERACTOR_3STATE_HPP
