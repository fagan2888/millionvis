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
#include <infovis/drawing/lite/LiteDisplacedLabel.hpp>
#include <infovis/drawing/gl_support.hpp>

namespace infovis {

LiteDisplacedLabel::LiteDisplacedLabel(const string& label,
				       const Point& orig,
				       justification j,
				       Font * font,
				       const Color& fg,
				       const Color& bg,
				       const Color& gfg)
  : LiteLabel(label, j, font, fg, bg, gfg),
    orig_(orig),
    line_alpha_(1.0f)
{
  setPosition(orig_);
  path_.push_back(orig_);
}

void
LiteDisplacedLabel::doRender(const RenderContext& c)
{
  if (grown_color_[Color::alpha] != 0 &&
      line_alpha_ != 0) {
    glColor4ub(grown_color_[Color::red],
	       grown_color_[Color::green],
	       grown_color_[Color::blue],
	       GLubyte(grown_color_[Color::alpha] * line_alpha_));
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    for (Path::const_iterator i = path_.begin();
	 i != path_.end(); i++) {
      set_vertex(*i);
    }
    //set_vertex(getPosition());
    glEnd();
  }
  if (line_alpha_ != 0) {
    glColor4ub(foreground_color_[Color::red],
	       foreground_color_[Color::green],
	       foreground_color_[Color::blue],
	       GLubyte(foreground_color_[Color::alpha] * line_alpha_));
    glLineWidth(1);
    glBegin(GL_LINE_STRIP);
    for (Path::const_iterator i = path_.begin();
	 i != path_.end(); i++) {
      set_vertex(*i);
    }
    //set_vertex(getPosition());
    glEnd();
  }
  LiteLabel::doRender(c);
}

Lite *
LiteDisplacedLabel::clone() const
{
  return new LiteDisplacedLabel(getLabel(),
				getOrig(),
				getJustification(),
				getFont(),
				getForegroundColor(),
				getBackgroundColor(),
				getGrownColor());
}

void
LiteDisplacedLabel::setLineAlpha(float alpha)
{
  line_alpha_ = alpha;
}

} // namespace infovis
