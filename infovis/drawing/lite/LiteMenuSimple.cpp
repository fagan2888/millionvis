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
#include <infovis/drawing/lite/LiteMenuSimple.hpp>
#include <infovis/drawing/lite/LiteLabel.hpp>
#include <infovis/drawing/Font.hpp>

namespace infovis {

LiteMenuSimple::LiteMenuSimple(Font * font,
			       const Color& fg,
			       const Color& c,
			       const Color& gfg)
  : LiteMenu(c),
    font_(font == 0 ? Font::create() : font),
    foreground_color_(fg),
    grown_color_(gfg)
{ }

Lite *
LiteMenuSimple::clone() const
{
  LiteMenuSimple * ret = new LiteMenuSimple(font_,
					    foreground_color_,
					    getColor(),
					    grown_color_);
  for (int i =0; i < labels_.size(); i++) {
    ret->addItem(getItem(i));
  }
  return ret;
}

Lite *
LiteMenuSimple::createLabel(const string& label)
{
  return new LiteLabel(label,
		       LiteLabel::just_left,
		       font_,
		       foreground_color_,
		       color_none,
		       grown_color_);
}

void
LiteMenuSimple::addItem(const string& str)
{
  labels_.push_back(str);
  LiteMenu::addChild(createLabel(str));
}

const string&
LiteMenuSimple::getItem(int index) const
{
  return labels_[index];
}

void
LiteMenuSimple::setChild(int index, Lite * l)
{
  Lite::setChild(index, l);
}

void
LiteMenuSimple::addChild(Lite * l)
{
  Lite::addChild(l);
}

void
LiteMenuSimple::insertChild(int pos, Lite * l)
{
  Lite::insertChild(pos, l);
}

void
LiteMenuSimple::eraseChild(int pos)
{
  if (pos >= 0 && pos < labels_.size()) {
    labels_.erase(labels_.begin()+pos);
    LiteMenu::eraseChild(pos);
  }
}


} // namespace infovis
