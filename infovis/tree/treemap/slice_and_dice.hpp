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
#ifndef INFOVIS_TREE_TREEMAP_SLICE_AND_DICE_HPP
#define INFOVIS_TREE_TREEMAP_SLICE_AND_DICE_HPP

#include <infovis/alloc.hpp>
#include <boost/config.hpp>
#include <infovis/tree/tree_traits.hpp>
#include <infovis/tree/tree_concepts.hpp>
#include <infovis/tree/sum_weight_visitor.hpp>
#include <infovis/drawing/direction.hpp>
#include <infovis/tree/treemap/treemap.hpp>
#include <infovis/tree/treemap/drawing/drawer.hpp>

namespace infovis {

/**
 * Implementation of the slice and dice treemap algorithm
 */
template <class Tree, 
	  class Box,
	  class WeightMap,
	  class Drawer = null_drawer<Tree,Box>,
          class Filter = filter_none>
struct treemap_slice_and_dice :
    public treemap<Tree,Box,WeightMap,Drawer,Filter>
{
  typedef treemap<Tree,Box,WeightMap,Drawer,Filter> super;
  typedef typename super::dist_type dist_type;
  typedef typename super::children_iterator children_iterator;
  typedef typename super::node_descriptor node_descriptor;

  treemap_slice_and_dice(const Tree& tree,
			 WeightMap wm,
			 Drawer drawer,
			 Filter filter)
    : super(tree, wm, drawer,filter)
  { }

  treemap_slice_and_dice(const Tree& tree,
			 WeightMap wm,
			 Drawer drawer = Drawer())
    : super(tree, wm, drawer)
  { }

  unsigned visit(direction dir, const Box& box,
		 typename tree_traits<Tree>::node_descriptor n,
		 unsigned depth = 0)
  {
    if (! drawer_.begin_box(box,n,depth))
      return 0;
    Box b(box);
    unsigned ret = 1;
    drawer_.draw_border(b, n, depth);
    if (is_leaf(n,tree_)) {
      drawer_.draw_box(b, n, depth);
    }
    else {
      const float tw = infovis::get(weight_, n);

      drawer_.begin_strip(box, n, depth, dir);
      if (dir == left_to_right) {
	dist_type w = width(b);
	float x = xmin(b); // + w * weight_[n] / (2*tw);

#if 0
	if (x > xmin(b)) {
	  drawer_.draw_box(Box(xmin(b),ymin(b),x,ymax(b)), n, depth);
	}
#endif
	children_iterator i,end;
	for (boost::tie(i,end) = children(n,tree_); i != end; i++) {
	  node_descriptor child = *i;
	  if (filter_(child))
	    continue;
	  float nw = w * infovis::get(weight_, child) / tw;
	  float e = /*(i == (end-1)) ? xmax(b) : */coord_type(x+nw);
	  ret += visit(flip(dir),
		       Box(x,ymin(b),e,ymax(b)),
		       child, depth+1);
	  x += nw;
	}
#if 0
	if (x < xmax(b)) {
	  drawer_.draw_box(Box(x,ymin(b),xmax(b),ymax(b)), n, depth);
	}
#endif
      }
      else {
	dist_type h = height(b);
	float y = ymin(b); // + h * weight_[n] / (2*tw);

#if 0
	if (y > ymin(b)) {
	  drawer_.draw_box(Box(xmin(b),ymin(b),xmax(b),y), n, depth);
	}
#endif
	children_iterator i,end;
	for (boost::tie(i,end) = children(n,tree_); i != end; i++) {
	  node_descriptor child = *i;
	  if (filter_(child))
	    continue;
	  float nh = h * infovis::get(weight_, child) / tw;
	  float e = /* (i == (end-1)) ? ymax(b) : */coord_type(y+nh);
	  ret += visit(flip(dir),
		       Box(xmin(b),y,xmax(b),e), child, depth+1);
	  y += nh;
	}
#if 0
	if (y < ymax(b)) {
	  drawer_.draw_box(Box(xmin(b),y,xmax(b),ymax(b)), n, depth);
	}
#endif
      }
      drawer_.end_strip(box, n, depth, dir);
    }
    drawer_.end_box(box,n,depth);
    return ret;
  }
};
} // namespace infovis

#endif // INFOVIS_TREE_TREEMAP_SLICE_AND_DICE_HPP
