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
#include <infovis/drawing/lite/LiteFrame.hpp>
#include <infovis/drawing/gl_support.hpp>

namespace infovis {

LiteFrame::LiteFrame(Lite * l, const Color& c, float width)
  : LiteProxy(l),
    color_(c),
    border_(c, width),
    width_(width)
{ }


Box
LiteFrame::getBounds() const
{
  return border_.growBox(LiteProxy::getBounds());
}

void
LiteFrame::setBounds(const Box& b)
{
  LiteProxy::setBounds(border_.shrinkBox(b));
}

void
LiteFrame::doRender(const RenderContext& rc)
{
  border_.render(rc, LiteProxy::getBounds());
  LiteProxy::doRender(rc);
}

Lite *
LiteFrame::clone() const
{
  return new LiteFrame(lite_->clone(), color_, border_.getWidth());
}

Interactor *
LiteFrame::interactor(const string& name, int tool_id)
{
  if (isA(name) && tool_id == mouse_id)
    return this;
  return 0;
}

bool
LiteFrame::doEnter(const Event&)
{
  border_.setInside(color_red);
  repaint();
  return true;
}

void
LiteFrame::doLeave(const Event&)
{
  border_.setInside(color_);
  repaint();
}

} // namespace infovis
