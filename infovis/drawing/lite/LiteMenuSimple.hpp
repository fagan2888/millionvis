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
#ifndef INFOVIS_DRAWING_LITE_MENUSIMPLE_HPP
#define INFOVIS_DRAWING_LITE_MENUSIMPLE_HPP

#include <infovis/drawing/lite/LiteMenu.hpp>
#include <vector>
#include <string>

namespace infovis {
class Font;

/**
 * Simple lite menu
 */
class LiteMenuSimple : public LiteMenu
{
public:
  LiteMenuSimple(Font * font = 0,
		 const Color& fg = color_black,
		 const Color& c = color_white,
		 const Color& gfg = color_none);

  Lite * clone() const;

  virtual void addItem(const string& str);
  virtual const string& getItem(int i) const;

  // Trap these functions to update the labels
  virtual void setChild(int index, Lite * l);
  virtual void addChild(Lite *);
  virtual void insertChild(int pos, Lite *);
  virtual void eraseChild(int pos);

protected:
  Lite * createLabel(const string& label);
  Font * font_;
  Color foreground_color_;
  Color grown_color_;
  std::vector<string,gc_alloc<string> > labels_;
};

} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_MENUSIMPLE_HPP
