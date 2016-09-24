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
#include <infovis/drawing/lite/LiteSliderExt.hpp>
#include <infovis/drawing/gl_support.hpp>

namespace infovis {

LiteSliderExt::LiteSliderExt(BoundedRangeObservable * observable,
			     const Box& bounds,
			     const Box& max_bounds,
			     direction dir,
			     const Color& fg,
			     const Color& bg,
			     Font * font)
  : LiteSlider(observable, bounds, dir, fg, bg, font),
    max_bounds_(max_bounds)
{ }

LiteSliderExt::LiteSliderExt(const Box& bounds,
			     const Box& max_bounds,
			     direction dir,
			     const Color& fg,
			     const Color& bg,
			     Font * font)
  : LiteSlider(bounds, dir, fg, bg, font),
    max_bounds_(max_bounds)
{ }

const Box&
LiteSliderExt::getMaxBounds() const { return max_bounds_; }

void
LiteSliderExt::setMaxBounds(const Box& v) {max_bounds_ = v; }

static float
inter(float min, float max, float t)
{
  return min * (1 - t) + max * t;
}

static float
param(float min, float max, float val)
{
  return (val - min) / (max - min);
}

Lite *
LiteSliderExt:: clone() const
{
  return new LiteSliderExt(getObservable(),
			   getBounds(),
			   getMaxBounds(),
			   getDirection(),
			   getForegroundColor(),
			   getBackgroundColor());
}

float
LiteSliderExt::getValue(const Point& pos, Zone) const
{
  float v = LiteSlider::getValue(pos);
  if (infovis::inside(bounds, x(pos), y(pos))) {
    return v;
  }
  float p;
  float min, max, val;

  if (direction_ == left_to_right || direction_ == right_to_left) {
    if (y(pos) < ymin(bounds)) {
      p = param(ymin(bounds), ymin(max_bounds_), y(pos));
    }
    else {
      p = param(ymax(bounds), ymax(max_bounds_), y(pos));
    }
    min = inter(xmin(bounds), xmin(max_bounds_), p);
    max = inter(xmax(bounds), xmax(max_bounds_), p);
    p = param(min, max, x(pos));
  }
  else {
    if (x(pos) < xmin(bounds)) {
      p = param(xmin(bounds), xmin(max_bounds_), x(pos));
    }
    else {
      p = param(xmax(bounds), xmax(max_bounds_), x(pos));
    }
    min = inter(ymin(bounds), ymin(max_bounds_), p);
    max = inter(ymax(bounds), ymax(max_bounds_), p);
    p = param(min, max, y(pos));
  }
  const BoundedRange * range = getObservable()->getBoundedRange();
  val = inter(range->min(), range->max(), p);
  if (val < range->min())
    val = range->min();
  else if (val > range->max())
    val = range->max();
  return val;
}
  

} // namespace infovis
