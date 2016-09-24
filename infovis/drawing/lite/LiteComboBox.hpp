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
#ifndef INFOVIS_DRAWING_LITE_LITECOMBOBOX_HPP
#define INFOVIS_DRAWING_LITE_LITECOMBOBOX_HPP

#include <infovis/drawing/lite/LiteSwitch.hpp>
#include <infovis/drawing/lite/LiteMenu.hpp>

namespace infovis {

/**
 * Combo Box
 */
class LiteComboBox : public LiteSwitch,
		     public Interactor3States,
		     public BoundedRangeObserver
{
public:
  LiteComboBox(LiteMenu * menu, int selected = 0);

  virtual Interactor * interactor(const string& name, int tool_id);
  virtual Lite * clone() const;

  virtual LiteMenu * getMenu() const;
  virtual void setMenu(LiteMenu * menu);
  virtual int getSelectedMenuItem() const;
  virtual void setSelectedMenuItem(int i);

  // Interactor3States
  virtual bool doStart(const Event& ev);
  virtual void doDrag(const Event& ev);
  virtual void doFinish(const Event& ev);

  // BoundedRangeObserver
  virtual void updateBoundedRange(BoundedRangeObservable * obs);
protected:
  LiteMenu * menu_;
  int selected_item_;
};

} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_LITECOMBOBOX_HPP
