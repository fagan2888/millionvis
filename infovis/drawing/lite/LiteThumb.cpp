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
#include <infovis/drawing/lite/LiteThumb.hpp>

namespace infovis {

LiteThumb::LiteThumb(LiteShape * shape,
		     LiteSlider * slider,
		     LiteSlider::Zone zone)
  : LiteEnterLeaveShape(shape, color_red, color_black),
    shape_(shape),
    slider_(slider),
    zone_(zone)
{ }

Lite *
LiteThumb::clone() const
{
  return new LiteThumb(shape_, slider_, zone_);
}

Interactor *
LiteThumb::interactor(const string& name, int tool_id)
{
  if (Interactor3States::isA(name))
    return (Interactor3States*)this;
  if (LiteEnterLeaveShape::isA(name))
    return (LiteEnterLeaveShape*)this;
  return 0;
}

bool
LiteThumb::doStart(const Event& ev)
{
  slider_->notifyBegin();
  BoundedRangeObservable * obs = slider_->getObservable();
  saved_ = obs->getBoundedRange()->value();
  saved_range_ = obs->getBoundedRange()->range();
  doDrag(ev);
  return true;
}

void
LiteThumb::doDrag(const Event& ev)
{
  BoundedRangeObservable * obs = slider_->getObservable();
  const BoundedRange * br = obs->getBoundedRange();
  float val, range;
  Point pos(getFieldPosition(ev));

  switch(zone_) {
  case LiteSlider::zone_min:
    val = slider_->getValue(pos, zone_);
    obs->notifyValueDragged(val);
    break;
  case LiteSlider::zone_thumb:
    val = slider_->getValue(pos, zone_);
    range = br->range();
    obs->notifyValueRangeDragged(val, range);
    break;
  case LiteSlider::zone_max:
    val = slider_->getValue(pos, zone_);
    range = val - br->value();
    obs->notifyRangeDragged(range);
    break;
  }
  repaint();
}

void
LiteThumb::doFinish(const Event& ev)
{
  doDrag(ev);
  slider_->notifyEnd();
  slider_->getObservable()->notifyBoundedRange();
}

void
LiteThumb::doAbort(const Event&)
{
  BoundedRangeObservable * obs = slider_->getObservable();
  obs->notifyValueDragged(saved_);
  obs->notifyRangeDragged(saved_range_);
  obs->notifyBoundedRange();
  slider_->notifyEnd();  
}


} // namespace infovis
