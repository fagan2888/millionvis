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
#ifndef INFOVIS_DRAWING_NOTIFIERS_CHANGE_HPP
#define INFOVIS_DRAWING_NOTIFIERS_CHANGE_HPP

#include <infovis/alloc.hpp>
#include <vector>

namespace infovis {

class ChangeObservable;

/**
 * Observer for Changed events
 */
class ChangeObserver
{
public:
  virtual ~ChangeObserver();

  virtual void changed(ChangeObservable *);
};

/**
 * Observable for Changed events
 */
class ChangeObservable
{
public:
  virtual ~ChangeObservable();
  virtual void addChangeObserver(ChangeObserver * obs) = 0;
  virtual void removeChangeObserver(ChangeObserver * obs) = 0;
  virtual void notifyChanged() = 0;
};

/**
 * Default implementation of Changed observable
 */
class DefaultChangeObservable
  : public std::vector<ChangeObserver*,gc_alloc<ChangeObserver*> >,
    public ChangeObservable
{
public:
  virtual void addChangeObserver(ChangeObserver * obs);
  virtual void removeChangeObserver(ChangeObserver * obs);
  virtual void notifyChanged();
};

} // namespace infovis

#endif // INFOVIS_DRAWING_NOTIFIERS_CHANGE_HPP
