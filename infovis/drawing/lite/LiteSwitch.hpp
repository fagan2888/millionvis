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
#ifndef INFOVIS_DRAWING_LITESWITCH_HPP
#define INFOVIS_DRAWING_LITESWITCH_HPP

#include <infovis/drawing/lite/LiteBox.hpp>

namespace infovis {

/**
 * Lite container showing one of its children
 */
class LiteSwitch : public LiteBox
{
public:
  LiteSwitch(bool change_bounds = true);

  virtual void render(const RenderContext&);
  virtual Lite * clone() const;

  virtual int getSelected() const;
  virtual void setSelected(int v);
  
  virtual void setChangeBounds(bool v);
  virtual bool getChangeBounds() const;

protected:
  virtual void computeBounds();
  int selected_;
  bool change_bounds_;
};

} // namespace infovis


#endif // INFOVIS_DRAWING_LITESWITCH_HPP
