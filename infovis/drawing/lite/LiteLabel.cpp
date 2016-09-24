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
#include <infovis/drawing/lite/LiteLabel.hpp>
#include <infovis/drawing/Font.hpp>
#include <infovis/drawing/box_io.hpp>
#include <infovis/drawing/gl_support.hpp>
#include <iostream>

namespace infovis {

LiteLabel::LiteLabel(const string& label,
		     justification justif,
		     Font * font, 
		     const Color& fg,
		     const Color& bg,
		     const Color& gfg)
  : label_(label),
    font_(font == 0 ? Font::create() : font),
    justif_(justif),
    foreground_color_(fg),
    background_color_(bg),
    grown_color_(gfg)
{
  bounds = getMinBounds();
}

Point
LiteLabel::getPosition() const
{
  switch(justif_) {
  default:
  case just_left:
  case just_fill:
    return Point(xmin(bounds), ymin(bounds));
  case just_center:
    return Point((xmin(bounds)+xmax(bounds))/2,
		 (ymin(bounds)+ymax(bounds))/2-font_->getDescent());
  case just_right:
    return Point(xmax(bounds), ymin(bounds));
  }
}

Point
LiteLabel::getStartPos() const
{
  float x, y;
    //std::cout << bounds << std::endl;
  switch(justif_) {
  case just_left:
  case just_fill:
    x = xmin(bounds);
    y = ymin(bounds)+font_->getDescent();
    break;
  case just_center: {
    Box mb(getMinBounds());
    x = xmin(bounds)+(width(bounds)-width(mb))/2;
    y = ymin(bounds)+(height(bounds)-height(mb))/2 +font_->getDescent();
    break;
  }
  case just_right: {
    Box mb(getMinBounds());
    x = xmax(bounds)-width(mb);
    y = ymax(bounds)-font_->getAscent();
  }
  }
  return Point(x,y);
}

void
LiteLabel::doRender(const RenderContext& c)
{
  if (background_color_[Color::alpha] != 0 || c.is_picking) {
    set_color(background_color_);
    draw_box(bounds);
  }
  const string& label = getLabel();
  if (c.is_picking) {
    return;
  }
  Point p = getStartPos();
  if (grown_color_[Color::alpha] != 0) {
    set_color(grown_color_);
    font_->paintGrown(label, x(p), y(p));
  }
  set_color(foreground_color_);
  font_->paint(label, x(p), y(p));
}

Lite *
LiteLabel::clone() const
{
  return new LiteLabel(label_, justif_, font_,
		       foreground_color_, background_color_, grown_color_);
}

const string&
LiteLabel::getLabel() const
{
  return label_;
}

void 
LiteLabel::setLabel(const string& label)
{
  label_ = label;
  bounds = getMinBounds();
}

Font *
LiteLabel::getFont() const
{
  return font_;
}

void
LiteLabel::setFont(Font * font)
{
  font_ = font;
}

const Color&
LiteLabel::getForegroundColor() const
{
  return foreground_color_;
}

void
LiteLabel::setForegroundColor(const Color& color)
{
  foreground_color_ = color;
}

const Color&
LiteLabel::getBackgroundColor() const
{
  return background_color_;
}

void
LiteLabel::setBackgoundColor(const Color& color)
{
  background_color_ = color;
}

const Color&
LiteLabel::getGrownColor() const
{
  return grown_color_;
}

void
LiteLabel::setGrownColor(const Color& color)
{
  grown_color_ = color;
}

LiteLabel::justification
LiteLabel::getJustification() const
{
  return justif_;
}

void
LiteLabel::setJustification(justification j)
{
  justif_ = j;
}

Box
LiteLabel::getMinBounds() const
{
  Box minBounds(font_->getStringBounds(label_));
  translate(minBounds, xmin(bounds), ymin(bounds)+font_->getDescent());
  return minBounds;
}

} // namespace infovis
