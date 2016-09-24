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
#ifndef INFOVIS_DRAWING_LITE_BORDER_HPP
#define INFOVIS_DRAWING_LITE_BORDER_HPP

#include <infovis/drawing/drawing.hpp>
#include <infovis/drawing/lite/Lite.hpp>

namespace infovis {

/**
 * Border for frames
 */
class Border {
public:
  enum Style {
    border_normal,
    border_raised,
    border_lower
  };
  Border(float w = 5);
  Border(const Color& inside, float w = 5);
  Border(const Color& inside, const Color& outside, float w = 5);
  virtual ~Border();

  virtual Box growBox(const Box& bounds) const;
  virtual Box shrinkBox(const Box& bounds) const;
  
  virtual float getWidth() const;
  virtual void setWidth(float w);
  
  virtual Style getStyle() const;
  virtual void setStyle(Style v);

  virtual const Color& getInside() const;
  virtual void setInside(const Color& v);

  
  virtual const Color& getOutside() const;
  virtual void setOutside(const Color& v);
  
  virtual void render(const Lite::RenderContext& c,
		      const Box& inBounds);
  
protected:
  
  Style style_;
  float width_;
  Color inside_;
  Color outside_;
};

} // namespace infovis 

#endif // INFOVIS_DRAWING_LITE_BORDER_HPP
