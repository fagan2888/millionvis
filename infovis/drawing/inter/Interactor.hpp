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
#ifndef INFOVIS_DRAWING_INTERACTOR_HPP
#define INFOVIS_DRAWING_INTERACTOR_HPP

#include <infovis/drawing/drawing.hpp>
#include <infovis/drawing/inter/Event.hpp>
#include <infovis/drawing/inter/EventCodes.hpp>

namespace infovis {

/**
 * Base interactor class.
 */
class Interactor : public virtual gc,
		   virtual public EventCodes
{
public:
  enum State {
    state_inactive,
    state_active
  };

  Interactor(const string& n) : name_(n), state_(state_inactive) { }
  virtual ~Interactor();

  const string& getInteractorName() const { return name_; }
  // transitions
  virtual bool activate(const Event&); // inactive->active
  virtual void desactivate(const Event&); // active->inactive
  virtual void abort(const Event&); // active->inactive

  virtual bool doActivate(const Event&); // inactive->active
  virtual void doDesactivate(const Event&); // active->inactive
  virtual void doAbort(const Event&); // active->inactive

  virtual bool isA(const string& n) const;
  State getState() const { return state_; }
  bool isActive() const { return state_ == state_active; }
  bool isInactive() const {return state_ == state_inactive; }
protected:
  string name_;
  State state_;
};


/**
 * Interactor for managing String events
 */
class StringInteractor : virtual public Interactor
{
public:
  StringInteractor() : Interactor("String") { }

  void receive(const Event&);

  virtual void doReceive(const Event&);
};

} // namespace infovis 

#endif // INFOVIS_DRAWING_INTERACTOR_HPP
