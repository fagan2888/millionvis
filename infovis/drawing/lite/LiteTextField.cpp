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
#include <infovis/drawing/lite/LiteTextField.hpp>
#include <infovis/drawing/Font.hpp>
#include <infovis/drawing/gl_support.hpp>

namespace infovis {

LiteTextField::LiteTextField(const string& text,
			     float width,
			     justification j,
			     Font * font,
			     const Color& fg,
			     const Color& bg,
			     const Color& gfg)
  : LiteLabel(text, j, font, fg, bg, gfg),
    caret_position_(text.length())
{
}

int
LiteTextField::getCaretPosition() const
{
  return caret_position_;
}

void
LiteTextField::setCaretPosition(unsigned pos)
{
  if (pos > getLabel().length())
    pos = getLabel().length();
  caret_position_ = pos;
}

void
LiteTextField::doRender(const RenderContext& c)
{
  LiteLabel::doRender(c);
  Point p = LiteLabel::getStartPos();
  if (caret_position_ != 0) {
    string s = getLabel().substr(0, caret_position_);
    set_x(p, x(p)+ font_->stringWidth(s));
  }
  set_color(foreground_color_);
  glBegin(GL_LINES);
  gl::vertex(x(p), y(p)-font_->getDescent());
  gl::vertex(x(p), y(p)-font_->getAscent());
  glEnd();
}

Lite *
LiteTextField::clone() const
{
  return new LiteTextField(label_,
			   width(bounds),
			   justif_,
			   font_,
			   foreground_color_,
			   background_color_,
			   grown_color_);
}

Interactor *
LiteTextField::interactor(const string& name, int toolid)
{
  if (Interactor3States::isA(name) && toolid == mouse_id) {
    Interactor3States* me = this;
    return me;
  }
  else if (KeyCodeInteractor::isA(name) && toolid == keyboard_id) {
    KeyCodeInteractor * me = this;
    return me;
  }
  return LiteLabel::interactor(name, toolid);
}
  
  // Interactor3States
bool
LiteTextField::doStart(const Event& ev)
{
  return false;
}

void
LiteTextField::doDrag(const Event& ev)
{
}

void
LiteTextField::doFinish(const Event& ev)
{
}

  // KeyCodeInteractor
void
LiteTextField::doKeyDown(KeyCode code)
{
}


} // namespace infovis
