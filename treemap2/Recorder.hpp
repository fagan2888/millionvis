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
#ifndef TREEMAP2_RECORDER_HPP
#define TREEMAP2_RECORDER_HPP

#include <infovis/drawing/notifiers/BoundedRange.hpp>
#include <types.hpp>
#include <ColorRamp.hpp>
#include <LiteTreemap.hpp>

namespace infovis {

struct RecordItem
{
  string weight;
  string color;
  string name;
  Ramp ramp;
  bool color_smooth;
  float color_min, color_range;
  string order;
  LiteTreemap::Layout layout;
  string x_axis;
  string y_axis;

  bool operator == (const RecordItem& other) const {
    return
      weight == other.weight &&
      color == other.color &&
      name == other.name &&
      ramp == other.ramp &&
      color_smooth == other.color_smooth &&
      color_min == other.color_min &&
      color_range == other.color_range &&
      order == other.order &&
      layout == other.layout &&
      x_axis == other.x_axis &&
      y_axis == other.y_axis;
  }
};

class Recorder : public std::vector<RecordItem>,
		 public BoundedRange,
		 public AbstractBoundedRangeObservable
{
public:
  typedef std::vector<RecordItem> super_vector;
  Recorder();

  void set_current(unsigned c);
  unsigned get_current() const;
  void advance(int i);
  void add(const RecordItem& r);
  const RecordItem& current() const;

  void load(std::istream& in);
  void load(const string& fname);
  void save(std::ostream& out);
  void save(const string& fname);

  size_t size() const { return super_vector::size(); }
  // BoundedRange
  virtual float min() const;
  virtual float max() const;
  virtual float value() const;
  virtual float range() const;

  // AbstractBoundedRangeObservable
  virtual const BoundedRange * getBoundedRange() const;
  virtual void notifyValueDragged(float v);

protected:
  unsigned current_;
};

} // namespace infovis


#endif // TREEMAP2_RECORDER_HPP
