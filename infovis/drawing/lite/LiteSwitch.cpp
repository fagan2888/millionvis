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
#include <infovis/drawing/lite/LiteSwitch.hpp>
#include <infovis/drawing/lite/LayoutStack.hpp>
#include <infovis/drawing/gl_support.hpp>

namespace infovis {

LiteSwitch::LiteSwitch(bool change_bounds)
  : LiteBox(new LayoutStack()),
    selected_(-1),
    change_bounds_(change_bounds)
{
}

void
LiteSwitch::render(const RenderContext& c)
{
  if (! is_visible)
    return;
  doRender(c);
  if (selected_ < 0 || selected_ >= childCount())
    return;
  if (c.is_picking)
    glPushName(selected_);
  getChild(selected_)->render(c);
  if (c.is_picking)
    glPopName();
}

Lite *
LiteSwitch::clone() const
{
  LiteBox * ret = new LiteSwitch(change_bounds_);
  for (List::const_iterator i = begin(); i != end(); i++)
    ret->addChild((*i)->clone());
  return ret;
}

int
LiteSwitch::getSelected() const { return selected_; }

void
LiteSwitch::setSelected(int v)
{
  selected_ = v;
  computeBounds();
}

void
LiteSwitch::setChangeBounds(bool v)
{
  change_bounds_ = v;
  computeBounds();
}

bool
LiteSwitch::getChangeBounds() const
{
  return change_bounds_;
}

void
LiteSwitch::computeBounds()
{
  bounds = layout_->doLayoutIn(this); // ignore the result
  if (change_bounds_) {
    if (selected_ >= 0 && selected_ < childCount())
      bounds = getChild(selected_)->getBounds();
    else
      bounds = Box();
  }
}

} // namespace infovis
