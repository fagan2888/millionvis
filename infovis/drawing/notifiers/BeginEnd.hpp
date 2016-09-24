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
#ifndef INFOVIS_DRAWING_NOTIFIERS_BEGINEND_HPP
#define INFOVIS_DRAWING_NOTIFIERS_BEGINEND_HPP

#include <infovis/alloc.hpp>
#include <vector>

namespace infovis {

class BeginEndObservable;

/**
 * Observer for begin/end sequences
 */ 
class BeginEndObserver
{
public:
  virtual ~BeginEndObserver();

  virtual void begin(BeginEndObservable *);
  virtual void end(BeginEndObservable *);
};

/**
 *Observable generating begin/end sequences
 */ 
class BeginEndObservable
{
public:
  virtual ~BeginEndObservable();
  virtual void addBeginEndObserver(BeginEndObserver * obs) = 0;
  virtual void removeBeginEndObserver(BeginEndObserver * obs) = 0;
  virtual void notifyBegin() = 0;
  virtual void notifyEnd() = 0;
};

/**
 * Default implementation of BeginEndObservable
 */
class DefaultBeginEndObservable
  : public std::vector<BeginEndObserver*, gc_alloc<BeginEndObserver*> >,
    public BeginEndObservable
{
public:
  virtual void addBeginEndObserver(BeginEndObserver * obs);
  virtual void removeBeginEndObserver(BeginEndObserver * obs);
  virtual void notifyBegin();
  virtual void notifyEnd();
};

} // namespace infovis

#endif // INFOVIS_DRAWING_NOTIFIERS_BEGINEND_HPP
