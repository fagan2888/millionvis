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
#ifndef INFOVIS_DRAWING_LITETABBED_HPP
#define INFOVIS_DRAWING_LITETABBED_HPP

#include <vector>
#include <string>

#include <infovis/drawing/lite/LiteSwitch.hpp>
#include <infovis/drawing/lite/LiteButton.hpp>

namespace infovis {

/**
 * Lite component that shows a tabbed pane.
 */
class LiteTabbed : public LiteBox,
		   public ChangeObserver
{
public:
  LiteTabbed();

  virtual Lite * clone() const;

  virtual void addTab(Lite * icon, Lite * tab);
  virtual void addTab(const std::string& name, Lite * tab);
  virtual void removeTab(int index);

  virtual LiteButton * getButton(int index) const;

  virtual int getSelected() const;
  virtual void setSelected(int v);

  // ChangeObserver
  virtual void changed(ChangeObservable *);
protected:
  LiteBox tabs_;
  LiteSwitch switch_;
};

} // namespace infovis


#endif // INFOVIS_DRAWING_LITETABBED_HPP
