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
#ifndef TREEMAP2_LAYOUTVISU_HPP
#define TREEMAP2_LAYOUTVISU_HPP

#include <LiteTreemap.hpp>
#include <infovis/alloc.hpp>
#include <infovis/tree/treemap/drawing/weight_interpolator.hpp>

namespace infovis {

struct Filter {
  const FilterColumn& filter_;

  Filter(const FilterColumn& filter)
    : filter_(filter)
  { }

  Filter(const Filter& other)
    : filter_(other.filter_)
  { }

  bool operator()(node_descriptor n) const {
    return filter_[n];
  }
};

class LayoutVisu
{
public:
  LayoutVisu(LiteTreemap * tm) : tm_(tm) { }
  virtual ~LayoutVisu();

  virtual unsigned draw(float param) = 0;
  virtual unsigned pick(float param) = 0;
  virtual void boxlist(float param,
		       AnimateTree::BoxList& bl, int depth) = 0;

  static LayoutVisu * create_visu(LiteTreemap::Layout l, LiteTreemap *);
protected:
  LiteTreemap * tm_;
};



} // namespace infovis

#endif // TREEMAP2_LAYOUTVISU_HPP
