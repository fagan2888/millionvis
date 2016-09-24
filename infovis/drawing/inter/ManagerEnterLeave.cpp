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
#include <infovis/drawing/inter/ManagerEnterLeave.hpp>
#include <infovis/drawing/inter/InteractorEnterLeave.hpp>
//#define PRINT
#ifdef PRINT
#include <iostream>
#endif

namespace infovis {

ManagerEnterLeave::ManagerEnterLeave()
{
  entered_ = true;
  initFieldEvent(event_);
}

void
ManagerEnterLeave::initFieldEvent(Event& ev)
{
  ev.clear();
  ev.addField(new FieldFloat(field_x));
  ev.addField(new FieldFloat(field_y));
  ev.addField(new FieldInt(field_mod));
}

const string&
ManagerEnterLeave::interactorName() const
{
  return getInteractorName();
}

ManagerEnterLeave::Stack
ManagerEnterLeave::pick(const Event& ev) const
{
  Stack stack;
  if (window_ == 0)
    return stack;

  if (! ev.hasField(field_x) || ! ev.hasField(field_y))
    return stack;

  float x = getFieldX(ev);
  float y = getFieldY(ev);
  const string& iname = interactorName();
  Pick pick;
  InteractorEnterLeave * inter;

  window_->pick(Box(x-1, y-1, x+1, y+1), pick);

  for (Pick::iterator i = pick.begin(); i != pick.end(); i++) {
    inter = dynamic_cast<InteractorEnterLeave*>((*i)->interactor(iname, mouse_id));
    if (inter != 0)
      stack.push_back(inter);
  }
  return stack;
}


void
ManagerEnterLeave::doDesactivate(const Event& ev)
{
  for (Stack::iterator i = inter_stack_.begin();
       i != inter_stack_.end(); i++) {
    (*i)->desactivate(ev);
  }
  inter_stack_.clear();
}

void
ManagerEnterLeave::doAbort(const Event& ev)
{
  for (Stack::iterator i = inter_stack_.begin();
       i != inter_stack_.end(); i++) {
    (*i)->abort(ev);
  }
  inter_stack_.clear();
}

struct not_entered {
  bool operator() (const InteractorEnterLeave * inter) const {
    return ! inter->isEntered();
  }
};

bool
ManagerEnterLeave::doEnter(const Event& ev)
{
  return true;
}

void
ManagerEnterLeave::doLeave(const Event& ev)
{
}

static bool find(const ManagerEnterLeave::Stack& stack,
		 const InteractorEnterLeave * item)
{
  return std::find(stack.begin(), stack.end(), item) != stack.end();
}

void
ManagerEnterLeave::doMove(const Event& ev)
{
  Stack stack = pick(ev);

  if (stack == inter_stack_) {
    for (Stack::iterator i = stack.begin();
	 i != stack.end(); i++) {
      InteractorEnterLeave * inter = *i;
      inter->move(ev);
    }
    return;
  }
  for (Stack::reverse_iterator ri = inter_stack_.rbegin();
       ri != inter_stack_.rend(); ri++) {
    InteractorEnterLeave * inter = *ri;
    if (! find(stack, inter)) {
      inter->leave(ev);
#ifdef PRINT
      std::cerr << "leaving " << inter << std::endl;
#endif
    }
  }
  inter_stack_.clear();

  for (Stack::iterator i = stack.begin();
       i != stack.end(); i++) {
    InteractorEnterLeave * inter = *i;
    if (inter->isEntered()) {
      inter_stack_.push_back(inter);
      inter->move(ev);
    }
    else if (inter->enter(ev)) {
      inter_stack_.push_back(inter);
#ifdef PRINT
      std::cerr << "entering " << inter << std::endl;
#endif
    }
  }
}

} // namespace infovis
