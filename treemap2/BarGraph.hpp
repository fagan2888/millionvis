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
#ifndef TREEMAP2_BARGRAPH_HPP
#define TREEMAP2_BARGRAPH_HPP

#include <infovis/drawing/drawing.hpp>
#include <infovis/drawing/direction.hpp>
#include <infovis/table/column.hpp>
#include <vector>

namespace infovis {

class BarGraph
{
public:
  typedef std::vector<float, gc_alloc<float, true> > List;
  BarGraph(unsigned bars);

  virtual void render(const Box& box, direction dir = left_to_right) const;

  void reset(float value = 0);
  virtual void setValue(unsigned index, float value);
  virtual float getValue(unsigned index) const;
  virtual void computeDistribution(const FloatColumn& values);
  virtual void computeDistribution(const FloatColumn& values,
				   float min_val, float max_val);
  
protected:
  void updateMinMax();
  List bars_;
  float min_;
  float max_;
};

} // namespace infovis

#endif // TREEMAP2_BARGRAPH_HPP
