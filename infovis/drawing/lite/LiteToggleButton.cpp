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
#include <infovis/drawing/lite/LiteToggleButton.hpp>
#include <infovis/drawing/lite/LiteRect.hpp>
#include <infovis/drawing/gl_support.hpp>

namespace infovis {

class LiteCross : public LiteBounded
{
public:
  LiteCross(const Box& b) : LiteBounded(b) { }

  void doRender(const RenderContext& c) {
    set_color(color_red);
    gl::begin_lines lines;
    gl::vertex(xmin(bounds), ymin(bounds));
    gl::vertex(xmax(bounds), ymax(bounds));
    gl::vertex(xmin(bounds), ymax(bounds));
    gl::vertex(xmax(bounds), ymin(bounds));
  }

  Lite * clone() const { return new LiteCross(bounds); }
};

LiteToggleButton::LiteToggleButton(int size)
  : LiteToggle(new LiteCross(Box(0, 0, size, size)),
	       new LiteRect(Box(0, 0, size, size), color_white))
{ }

Lite *
LiteToggleButton::clone() const
{
  return new LiteToggleButton();
}

Interactor *
LiteToggleButton::interactor(const string& name, int tool_id)
{
  if (isA(name) && tool_id == mouse_id)
    return this;
  return 0;
}

void
LiteToggleButton::doFinish(const Event& ev)
{
  if (infovis::inside(getBounds(), getFieldX(ev), getFieldY(ev)))
    toggle();
  repaint();
}

} // namespace infovis
