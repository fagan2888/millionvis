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
#ifndef INFOVIS_DRAWING_LITE_LITELABEL_HPP
#define INFOVIS_DRAWING_LITE_LITELABEL_HPP

#include <infovis/drawing/lite/LiteBounded.hpp>

namespace infovis {
class Font;

/**
 * Lite displaying a one-line text.
 */
class LiteLabel : public LiteBounded
{
public:
  enum justification {
    just_left,
    just_center,
    just_right,
    just_fill
  };
  LiteLabel(const string& label, 
	    justification j = just_left,
	    Font * font = 0,
	    const Color& fg = color_black,
	    const Color& bg = color_white,
	    const Color& gfg = color_none);

  virtual Box getMinBounds() const;

  virtual Point getPosition() const;

  virtual void doRender(const RenderContext& c);
  virtual Lite * clone() const;

  virtual const string& getLabel() const;
  virtual void setLabel(const string& lab);

  virtual justification getJustification() const;
  virtual void setJustification(justification j);

  virtual Font * getFont() const;
  virtual void setFont(Font * font);

  virtual const Color& getForegroundColor() const;
  virtual void setForegroundColor(const Color& color);

  virtual const Color& getBackgroundColor() const;
  virtual void setBackgoundColor(const Color& color);

  virtual const Color& getGrownColor() const;
  virtual void setGrownColor(const Color& color);

  virtual Point getStartPos() const;

protected:
  string label_;
  justification justif_;
  Font * font_;
  Color foreground_color_;
  Color background_color_;
  Color grown_color_;
};

} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_LITELABEL_HPP
