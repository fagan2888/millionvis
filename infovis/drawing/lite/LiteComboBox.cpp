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
#include <infovis/drawing/lite/LiteComboBox.hpp>

namespace infovis {

LiteComboBox::LiteComboBox(LiteMenu * menu, int selected)
  : LiteSwitch(),
    menu_(menu),
    selected_item_(selected)
{
  Lite * l = menu->getChild(selected);
  if (l != 0)
    addChild(l->clone());
  else
    addChild(new LiteGroup());
  setSelected(0);
  menu_->setVisible(false);
  menu_->setSelected(selected);
  menu_->addBoundedRangeObserver(this);
  addChild(menu_);
}

Interactor *
LiteComboBox::interactor(const string& name, int tool_id)
{
  if (isA(name) && tool_id == mouse_id)
    return this;
  return 0;
}

Lite *
LiteComboBox::clone() const
{
  return new LiteComboBox(dynamic_cast<LiteMenu*>(menu_->clone()),
			  menu_->getSelected());
}

LiteMenu *
LiteComboBox::getMenu() const { return menu_; }

void
LiteComboBox::setMenu(LiteMenu * menu)
{
  removeChild(menu_);
  menu_ = menu;
  addChild(menu_);
  selected_item_ = -1;		// force re-creation of visible item
  updateBoundedRange(menu_);
}

int
LiteComboBox::getSelectedMenuItem() const
{
  return selected_item_;
}

void
LiteComboBox::setSelectedMenuItem(int i)
{
  if (i >= 0 && i < menu_->max() &&
      selected_item_ != i) {
    menu_->setSelected(i);
    selected_item_ = menu_->getSelected();
    Lite * l = menu_->getChild(selected_item_);
    if (l != 0) {
      l = l->clone();
      setChild(0, l);
    }
  }
}

bool
LiteComboBox::doStart(const Event& ev)
{
  Event nev(ev);
  setFieldPosition(nev, getPosition());

  setSelected(1);
  return menu_->start(nev);
}

void
LiteComboBox::doDrag(const Event& ev)
{
  menu_->drag(ev);
}

void
LiteComboBox::doFinish(const Event& ev)
{
  menu_->finish(ev);
  setSelected(0);
  repaint();
}

void
LiteComboBox::updateBoundedRange(BoundedRangeObservable *)
{
  if (menu_->getSelected() >= 0 &&
      selected_item_ != menu_->getSelected()) {
    selected_item_ = menu_->getSelected();
    Lite * l = menu_->getChild(selected_item_);
    if (l != 0) {
      l = l->clone();
      setChild(0, l);
    }
  }
}


} // namespace infovis
