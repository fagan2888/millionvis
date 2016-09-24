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
#ifndef INFOVIS_TREE_DRAWING_TREEMAP_PICK_DRAWER_HPP
#define INFOVIS_TREE_DRAWING_TREEMAP_PICK_DRAWER_HPP

#include <infovis/tree/tree_traits.hpp>
#include <infovis/tree/treemap/drawing/drawer.hpp>
#include <infovis/tree/treemap/drawing/border_drawer.hpp>
#include <infovis/drawing/box.hpp>

namespace infovis {

template <class Tree, class Box, 
	  class BorderDrawer = border_drawer<Tree,Box> >
class pick_drawer : public null_drawer<Tree,Box>
{
protected:
  typedef typename box_traits<Box>::coord_type coord_type;
  typedef typename tree_traits<Tree>::node_descriptor node_descriptor;

  coord_type x, y;
  node_descriptor picked;
  int picked_depth;
  BorderDrawer border;
public:
  pick_drawer(coord_type X, coord_type Y)
    : x(X), y(Y), picked_depth(-1) {}
  pick_drawer()
    : x(0), y(0), picked_depth(-1) {}

  void start() { picked_depth=-1; }
  void finish() { }

  void reset(coord_type X, coord_type Y) { x=X; y=Y; }

  bool begin_box(const Box& b,
		 typename tree_traits<Tree>::node_descriptor n,
		 unsigned depth) {
    if (! inside(b, x, y))
      return false;
    if (int(depth) <= picked_depth)
      return false;
    picked = n;
    picked_depth = depth;
    return true;
  }
  void draw_box(const Box& b,
		typename tree_traits<Tree>::node_descriptor n,
		unsigned depth) { }
  void draw_border(Box& b, 
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth) {
    if (border.begin_border(b, n, depth)) {
      border.remaining_box(b, n, depth);
    }
  }
  void remove_border(Box& b, 
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth) {
    draw_border(b, n, depth);
  }
  void end_box(const Box& b, 
	       typename tree_traits<Tree>::node_descriptor n,
	       unsigned depth) { }

  node_descriptor picked_node() const { return picked; }
  bool has_picked() const { return picked_depth != -1; }
};

} // namespace infovis


#endif // INFOVIS_TREE_DRAWING_TREEMAP_PICK_DRAWER_HPP
