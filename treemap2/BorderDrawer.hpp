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
#ifndef TREEMAP2_BORDERDRAWER_HPP
#define TREEMAP2_BORDERDRAWER_HPP

#include <infovis/drawing/notifiers/BoundedRange.hpp>
#include <infovis/tree/treemap/drawing/border_drawer.hpp>
#include <types.hpp>

namespace infovis {

struct BorderDrawer : public DefaultBoundedRangeObservable
{
  BorderDrawer(const Tree& t)
    : DefaultBoundedRangeObservable(1, 10, 1), tree_(t) {  }

  bool begin_border(const Box& b, 
		    node_descriptor n,
		    unsigned depth) const {
    if (is_leaf(n, tree_))
      return false;
    else
      return width(b) > (2+value_) && height(b) > (2+value_);
  }
  bool left_border(Box& b, 
		   node_descriptor n,
		   unsigned depth) const {
    if (! is_leaf(n, tree_))
      b = Box(xmin(b), ymax(b)-value_, xmax(b), ymax(b));
    return true;
  }
  bool right_border(Box& b, 
		   node_descriptor n,
		    unsigned depth) const {
    return false;
  }
  bool top_border(Box& b, 
		  node_descriptor n,
		  unsigned depth) const {
    if (! is_leaf(n, tree_))
      b = Box(xmin(b), ymin(b), xmin(b)+value_, ymax(b)-value_);
    return true;
  }
  bool bottom_border(Box& b, 
		     node_descriptor n,
		     unsigned depth) const {
    return false;
  }
  void remaining_box(Box& b,
		     node_descriptor n,
		     unsigned depth) const {
    if (! is_leaf(n, tree_)) {
      set_xmin(b,xmin(b)+value_);
      set_ymax(b,ymax(b)-value_);
    }
  }  

  const Tree& tree_;
};

} // namespace infovis

#endif // TREEMAP2_BORDERDRAWER_HPP
