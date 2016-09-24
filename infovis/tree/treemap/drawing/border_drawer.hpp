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
#ifndef INFOVIS_TREE_TREEMAP_DRAWING_BORDER_DRAWER_HPP
#define INFOVIS_TREE_TREEMAP_DRAWING_BORDER_DRAWER_HPP

#include <infovis/tree/tree_traits.hpp>
#include <infovis/drawing/box.hpp>

namespace infovis {

/**
 * Class for drawing border
 */
template <class Tree, class Box>
struct border_drawer
{
  typedef typename box_traits<Box>::coord_type coord_type;

  bool begin_border(Box& b, 
		    typename tree_traits<Tree>::node_descriptor n,
		    unsigned depth) const {
    return (width(b) > 3 && height(b) > 3);
  }
  bool left_border(Box& b, 
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth) const {
    b = Box(xmin(b), ymax(b)-1, xmax(b), ymax(b));
    return true;
  }
  bool right_border(Box& b, 
		   typename tree_traits<Tree>::node_descriptor n,
		    unsigned depth) const {
    return false;
  }
  bool top_border(Box& b, 
		  typename tree_traits<Tree>::node_descriptor n,
		  unsigned depth) const {
    b = Box(xmin(b), ymin(b), xmin(b)+1, ymax(b)-1);
    return true;
  }
  bool bottom_border(Box& b, 
		     typename tree_traits<Tree>::node_descriptor n,
		     unsigned depth) const {
    return false;
  }
  void remaining_box(Box& b,
		     typename tree_traits<Tree>::node_descriptor n,
		     unsigned depth) const {
    set_xmin(b,xmin(b)+1);
    set_ymax(b,ymax(b)-1);
  }
};


} // namespace infovis

#endif // INFOVIS_TREE_TREEMAP_DRAWING_BORDER_DRAWER_HPP
