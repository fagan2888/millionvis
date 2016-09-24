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
#include <infovis/drawing/lite/LiteGroup.hpp>
#include <algorithm>

namespace infovis {

LiteGroup::LiteGroup()
  : is_fixed_(false)
{ }

LiteGroup::LiteGroup(const Box& b)
  : LiteBounded(b),
    is_fixed_(true)
{ }

LiteGroup::~LiteGroup() { }

void
LiteGroup::setPosition(const Point& p)
{
  Vector v = p - getPosition();

  for (List::iterator i = group_.begin(); i != group_.end(); i++) {
    (*i)->setPosition((*i)->getPosition() + v);
  }
  LiteBounded::setPosition(p);
}

Lite *
LiteGroup::clone() const
{
  LiteGroup * ret = new LiteGroup();

  for (List::const_iterator i = group_.begin(); i != group_.end(); i++)
    ret->addChild((*i)->clone());
  return ret;
}
int
LiteGroup::childCount() const { return group_.size(); }
Lite *
LiteGroup::getChild(int index) const
{
  if (index >= 0 && index < group_.size())
    return group_[index];
  return 0;
}

void
LiteGroup::setChild(int index, Lite *l )
{
  if (index >= 0 && index < group_.size()) {
    group_[index] = l;
    computeBounds();		// should be optimized
  }

}

void
LiteGroup::addChild(Lite * c)
{
  group_.push_back(c);
  computeBounds();		// should be optimized
}

void
LiteGroup::insertChild(int i, Lite * l)
{
  if (i >= 0 && i <= childCount()) {
    group_.insert(group_.begin()+i, l);
    computeBounds();		// should be optimized
  }
}

void
LiteGroup::eraseChild(int i)
{
  if (i >= 0 && i < childCount()) {
    group_.erase(group_.begin()+i);
    computeBounds();		// should be optimized
  }
}

Lite::iterator
LiteGroup::begin()
{
  return group_.begin();
}

Lite::const_iterator
LiteGroup::begin() const
{
  return group_.begin();
}

Lite::iterator
LiteGroup::end()
{
  return group_.end();
}

Lite::const_iterator
LiteGroup::end() const
{
  return group_.end();
}

void
LiteGroup::setFixed(bool f)
{
  is_fixed_ = f;
  if (! is_fixed_)
    computeBounds();
}

void
LiteGroup::computeBounds()
{
  if (isFixed())
    return;
  if (group_.size() == 0) {
    bounds = Box();
    return;
  }
  List::const_iterator i = group_.begin();
  bounds = (*i)->getBounds();
  for (++i; i != group_.end(); ++i) {
    bounds = box_union(bounds, (*i)->getBounds());
  }
}

bool
LiteGroup::isFixed() const
{
  return is_fixed_;
}

} // namespace infovis
