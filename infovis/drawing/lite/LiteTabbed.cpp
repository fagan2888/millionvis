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
#include <infovis/drawing/lite/LiteButton.hpp>
#include <infovis/drawing/lite/LiteFrame.hpp>
#include <infovis/drawing/lite/LiteLabel.hpp>
#include <infovis/drawing/lite/LiteTabbed.hpp>

namespace infovis {

LiteTabbed::LiteTabbed()
  : tabs_(new LayoutBox(LayoutBox::horizontal)),
    switch_(false)
{
  addChild(&switch_);
  addChild(&tabs_);
}

Lite *
LiteTabbed::clone() const
{
  LiteTabbed * ret = new LiteTabbed();
  // FIXME +++
  return ret;
}

void
LiteTabbed::addTab(Lite * icon, Lite * tab)
{
  LiteButton * button = new LiteButton(new LiteFrame(icon, color_black, 2));
  button->addChangeObserver(this);
  tabs_.addChild(button);
  switch_.addChild(tab);
  tabs_.invalidate();
  switch_.invalidate();
  invalidate();
}

void
LiteTabbed::addTab(const std::string& name, Lite * tab)
{
  addTab(new LiteLabel(name, LiteLabel::just_center, 0, color_black, color_none), tab);
}

void
LiteTabbed::removeTab(int index)
{
  LiteButton * b = getButton(index);
  if (b == 0)
    return;
  b->removeChangeObserver(this);
  tabs_.eraseChild(index);
  switch_.eraseChild(index);
}

LiteButton *
LiteTabbed::getButton(int index) const
{
  return dynamic_cast<LiteButton*>(tabs_.getChild(index));
}

int
LiteTabbed::getSelected() const
{
  return switch_.getSelected();
}

void
LiteTabbed::setSelected(int v)
{
  switch_.setSelected(v);
}


void
LiteTabbed::changed(ChangeObservable * obs)
{
  for (int i = 0; i < tabs_.childCount(); i++) {
    LiteButton * b = getButton(i);
    if (b == obs) {
      setSelected(i);
      return;
    }
  }
}


} // namespace infovis
