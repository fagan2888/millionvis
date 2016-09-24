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
#ifndef INFOVIS_DRAWING_LITE_RANGESLIDER_HPP
#define INFOVIS_DRAWING_LITE_RANGESLIDER_HPP

#include <infovis/drawing/lite/LiteSlider.hpp>

namespace infovis {
class Font;

/**
 * Lite component implementing a range slider.
 */
class LiteRangeSlider : public LiteSlider
{
public:
  LiteRangeSlider(BoundedRangeObservable * observable,
		  const Box& bounds,
		  direction dir = left_to_right,
		  const Color& fg = color_black,
		  const Color& bg = color_white,
		  Font * font = 0,
		  float minmax_size = 10
		  );
  LiteRangeSlider(const Box& bounds,
		  direction dir = left_to_right,
		  const Color& fg = color_black,
		  const Color& bg = color_white,
		  Font * font = 0,
		  float minmax_size = 10
		  );


  virtual Lite * clone() const;

  virtual float getMinSize() const;
  virtual void setMinSize(float v);

  virtual float getMaxSize() const;
  virtual void setMaxSize(float v);

  virtual string maxLabel();

protected:
  float min_size_;
  float max_size_;
  float saved_range_;
  Zone zone_dragged_;
};


} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_RANGESLIDER_HPP
