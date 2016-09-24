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
#ifndef INFOVIS_DRAWING_INTERACTOR_MANAGERENTERLEAVE_HPP
#define INFOVIS_DRAWING_INTERACTOR_MANAGERENTERLEAVE_HPP

#include <infovis/drawing/inter/InteractorManager.hpp>
#include <infovis/drawing/inter/InteractorEnterLeave.hpp>

#include <vector>

namespace infovis {

/**
 * Manages EnterLeave interactors 
 */
class ManagerEnterLeave : public InteractorEnterLeave,
			  public InteractorManager
{
public:
  typedef std::vector<InteractorEnterLeave *> Stack;
  ManagerEnterLeave();

  // InteractorManager
  virtual const string& interactorName() const;

  // Interactor
  virtual void doDesactivate(const Event& ev); // active->inactive
  virtual void doAbort(const Event& ev);	// active->inactive

  Stack pick(const Event& ev) const;

  virtual bool doEnter(const Event& ev);
  virtual void doLeave(const Event& ev);
  virtual void doMove(const Event& ev);

  void initFieldEvent(Event& ev); // not virtual
protected:
  Stack inter_stack_;
};

} // namespace infovis

#endif // INFOVIS_DRAWING_INTERACTOR_MANAGERENTERLEAVE_HPP