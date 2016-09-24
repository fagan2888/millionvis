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
#ifndef INFOVIS_DRAWING_INTERACTORMANAGER_HPP
#define INFOVIS_DRAWING_INTERACTORMANAGER_HPP

#include <infovis/drawing/inter/Interactor.hpp>
#include <infovis/drawing/lite/LiteWindow.hpp>

namespace infovis {

/**
 * Base class for interactor managers.
 */
class InteractorManager : virtual public EventCodes
{
public:
  typedef LiteWindow::List Pick;

  InteractorManager();
  virtual ~InteractorManager();

  virtual const string& interactorName() const = 0;

  virtual void connect(LiteWindow *);
  virtual void disconnect(LiteWindow *);
  virtual Interactor * pick(const Event& ev);

  virtual LiteWindow * getWindow() const;
  Event& getEvent() { return event_; }
  const Event& getEvent() const { return event_; }

protected:
  LiteWindow * window_;
  Event event_;
};

} // namespace infovis 

#endif // INFOVIS_DRAWING_INTERACTORMANAGER_HPP

