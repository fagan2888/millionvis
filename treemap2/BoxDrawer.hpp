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
#ifndef TREEMAP2_BOXDRAWER_HPP
#define TREEMAP2_BOXDRAWER_HPP

#include <infovis/tree/tree_traits.hpp>
#include <infovis/tree/treemap/drawing/border_drawer.hpp>
#include <BorderDrawer.hpp>
#include <vector>

namespace infovis {

struct BoxDrawer : public null_drawer<Tree,Box>
{
  typedef std::vector<Box, gc_alloc<Box,true> > BoxList;

  BoxDrawer(const BorderDrawer& b, BoxList& bm)
    : border_(b), boxes_(bm), depth_(0)
  { }

  void set_depth(unsigned d) { depth_ = d; }
  unsigned get_depth() const { return depth_; }
  void start() { }
  void push(const Box& b, node_descriptor n) {
    boxes_[n] = b;
  }
  bool begin_box(const Box& b,
		 node_descriptor n,
		 unsigned depth) {
    return
      depth <= depth_;
  }
  void draw_box(const Box& b,
		node_descriptor n,
		unsigned depth) {
    if (depth < depth_)
      push(b, n);
  }
  void draw_border(Box& b, 
		   node_descriptor n,
		   unsigned depth) {
    if (border_.begin_border(b, n, depth)) {
      border_.remaining_box(b, n, depth);
    }
    if (depth == depth_)
      push(b, n);
  }
  void remove_border(Box& b, 
		   node_descriptor n,
		   unsigned depth) {
    if (border_.begin_border(b, n, depth)) {
      border_.remaining_box(b, n, depth);
    }
  }
  void end_box(const Box& b, 
	       node_descriptor n,
	       unsigned depth) { }

  void finish() { }
  const BoxList& getBoxes() const { return boxes_; }

protected:
  const BorderDrawer& border_;
  BoxList& boxes_;
  unsigned depth_;
};

} // namespace infovis

#endif // TREEMAP2_BOXDRAWER_HPP
