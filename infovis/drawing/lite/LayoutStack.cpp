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
#include <infovis/drawing/lite/LayoutStack.hpp>
#include <algorithm>

namespace infovis {

LayoutStack::LayoutStack()
{ }

LayoutStack::~LayoutStack()
{ }

Layout *
LayoutStack::clone() const
{
  return new LayoutStack();	// don't copy contents
}

void
LayoutStack::setLite(int index, Lite* l)
{
  if (index >= 0 && index < lite_.size())
    lite_[index] = l;
}

void
LayoutStack::addLite(Lite * l)
{
  lite_.push_back(l);
}

void
LayoutStack::removeLite(Lite * l)
{
  Lite::List::iterator i = std::find(lite_.begin(), lite_.end(), l);
  if (i != lite_.end())
    lite_.erase(i);
}

void
LayoutStack::insertLite(int i, Lite * l)
{
  if (i >= 0 && i <= lite_.size())
    lite_.insert(lite_.begin()+i, l);
}

void
LayoutStack::eraseLite(int i)
{
  if (i >= 0 && i < lite_.size())
    lite_.erase(lite_.begin()+i);
}

Box
LayoutStack::doLayoutIn(Lite * container)
{
  Vector size(0, 0);

  Box b(container->getBounds());
  Point p(min(b));
  for (Lite::List::const_iterator i = lite_.begin();
       i != lite_.end(); i++) {
    Lite * l = *i;
    Box b(l->getBounds());
    Vector v(extent(b));

    l->movePosition(p-min(b));
    set_dx(size, std::max(dx(size),dx(v)));
    set_dy(size, std::max(dy(size),dy(v)));
  }
  container->setSize(size);
  return Box(min(b),size);
}

} // namespace infovis
