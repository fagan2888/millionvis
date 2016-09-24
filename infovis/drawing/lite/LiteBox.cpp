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
#include <infovis/drawing/lite/LiteBox.hpp>

namespace infovis {

LiteBox::LiteBox(Layout * l) : layout_(l) { is_fixed_ = true; }

Lite *
LiteBox::clone() const
{
  LiteBox * ret = new LiteBox(layout_->clone());
  for (List::const_iterator i = begin(); i != end(); i++)
    ret->addChild((*i)->clone());
  return ret;
}

void
LiteBox::setChild(int index, Lite * l)
{
  getLayout()->setLite(index, l);
  LiteGroup::setChild(index, l);
}

void
LiteBox::addChild(Lite * l)
{
  layout_->addLite(l);
  LiteGroup::addChild(l);
}

void
LiteBox::removeChild(Lite * l)
{
  layout_->removeLite(l);
  LiteGroup::removeChild(l);
}

void
LiteBox::insertChild(int pos, Lite * l)
{
  getLayout()->insertLite(pos, l);
  LiteGroup::insertChild(pos, l);
}

void
LiteBox::eraseChild(int pos)
{
  getLayout()->eraseLite(pos);
  LiteGroup::eraseChild(pos);
}

Layout *
LiteBox::getLayout() const { return layout_; }

void
LiteBox::setLayout(Layout* v)
{
  //delete layout_;
  layout_ = v;
  for (int i = 0; i < childCount(); i++)
    layout_->addLite(getChild(i));
}

void
LiteBox::computeBounds()
{
  bounds = layout_->doLayoutIn(this);
}

void
LiteBox::pack()
{
  computeBounds();
}

} // namespace infovis
