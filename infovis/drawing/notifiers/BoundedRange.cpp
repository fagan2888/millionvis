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
#include <infovis/drawing/notifiers/BoundedRange.hpp>
#include <algorithm>

namespace infovis {


BoundedRange::~BoundedRange() { }

DefaultBoundedRange::DefaultBoundedRange(float m, float M, float v, float r)
  : min_(m), max_(M), value_(v), range_(r)
{ }

DefaultBoundedRange::DefaultBoundedRange(const BoundedRange& other)
  : min_(other.min()),
    max_(other.max()),
    value_(other.value()),
    range_(other.range())
{ }

const DefaultBoundedRange&
DefaultBoundedRange::operator = (const BoundedRange& other)
{
  min_ = other.min();
  max_ = other.max();
  value_ = other.value();
  range_ = other.range();
  return *this;
}

float
DefaultBoundedRange::min() const
{
  return min_;
}

float
DefaultBoundedRange::max() const
{
  return max_;
}

float
DefaultBoundedRange::value() const
{
  return value_;
}

float
DefaultBoundedRange::range() const
{
  return range_;
}

void
DefaultBoundedRange::set_min(float v)
{
  min_ = v;
  set_value(value_);		// check bounds
}
void
DefaultBoundedRange::set_max(float v)
{
  max_ = v;
  set_value(value_);		// check bounds
}

void
DefaultBoundedRange::set_value(float v)
{
  float vr = value_ + range_;
  if (v < min_)
    v = min_;
  else if (v > max_)
    v = max_;
  if (v > vr)
    vr = v;
  value_ = v;
  range_ = vr - v;
}

void
DefaultBoundedRange::set_range(float r)
{
  if (r < 0)
    return;
  float vr = value_ + r;
  if (vr > max_)
    vr = max_;
  range_ = vr - value_;
  set_value(value_);		// check bounds
}

void
DefaultBoundedRange::set_value_range(float v, float r)
{
  if (v < min_)
    v = min_;
  float vr = v + r;
  if (vr > max_) {
    vr = max_;
    v = vr - r;
  }
  value_ = v;
  range_ = vr - v;
}

BoundedRangeObserver::~BoundedRangeObserver() { }
void
BoundedRangeObserver::valueDragged(BoundedRangeObservable *) { }

void
BoundedRangeObserver::rangeDragged(BoundedRangeObservable *) { }
void
BoundedRangeObserver::updateBoundedRange(BoundedRangeObservable *) { }

BoundedRangeObservable::~BoundedRangeObservable() { }

void
AbstractBoundedRangeObservable::addBoundedRangeObserver(BoundedRangeObserver * obs)
{
  push_back(obs);
}

void
AbstractBoundedRangeObservable::removeBoundedRangeObserver(BoundedRangeObserver * obs)
{
  iterator i = std::find(begin(), end(), obs);
  if (i != end())
    erase(i);
}

void
AbstractBoundedRangeObservable::notifyValueDragged(float v)
{
  for (const_iterator i = begin(); i != end(); i++) {
    (*i)->valueDragged(this);
  }
}

void
AbstractBoundedRangeObservable::notifyRangeDragged(float r)
{
  for (const_iterator i = begin(); i != end(); i++) {
    (*i)->rangeDragged(this);
  }
}

void
AbstractBoundedRangeObservable::notifyValueRangeDragged(float v, float r)
{
  for (const_iterator i = begin(); i != end(); i++) {
    (*i)->valueDragged(this);
    (*i)->rangeDragged(this);
  }
}

void
AbstractBoundedRangeObservable::notifyBoundedRange()
{
  for (const_iterator i = begin(); i != end(); i++) {
    (*i)->updateBoundedRange(this);
  }
}

const BoundedRange *
DefaultBoundedRangeObservable::getBoundedRange() const
{
  return this;
}

void
DefaultBoundedRangeObservable::notifyValueDragged(float v)
{
  set_value(v);
  AbstractBoundedRangeObservable::notifyValueDragged(v);
}

void
DefaultBoundedRangeObservable::notifyRangeDragged(float r)
{
  set_range(r);
  AbstractBoundedRangeObservable::notifyRangeDragged(r);
}

void
DefaultBoundedRangeObservable::notifyValueRangeDragged(float v, float r)
{
  set_value_range(v, r);
  AbstractBoundedRangeObservable::notifyValueRangeDragged(v, r);
}

} // namespace infovis
