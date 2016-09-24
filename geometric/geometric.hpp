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
#ifndef INFOVIS_TREE_TREEMAP_GEOMETRIC_HPP
#define INFOVIS_TREE_TREEMAP_GEOMETRIC_HPP

#include <infovis/alloc.hpp>
#include <infovis/config.hpp>
#include <infovis/tree/tree_traits.hpp>
#include <infovis/tree/tree_concepts.hpp>
#include <infovis/tree/treemap/drawing/drawer.hpp>

#include <algorithm>
#include <cassert>

namespace infovis {

template <class Tree,
	  class Box,
	  class TotalWeightMap,
	  class Drawer = null_drawer<Tree,Box>,
	  class Map = TotalWeightMap
>
class treemap_geometric {
  const Tree& tree_;
  TotalWeightMap total_weight_;
  Map xmap_;
  Map ymap_;
  Drawer drawer_;

  struct indirect_compare {
    typedef typename tree_traits<Tree>::node_descriptor node_descriptor;
    Map map_;
    indirect_compare(Map map) : map_(map) { }
    bool operator() (node_descriptor n1, node_descriptor n2) const {
      return boost::get(map_, n1) < boost::get(map_, n2);
    }
  };
public:
  typedef Box box_type;
  typedef typename box_traits<Box>::coord_type coord_type;
  typedef typename box_traits<Box>::dist_type dist_type;
  typedef typename tree_traits<Tree>::children_iterator children_iterator;
  typedef typename tree_traits<Tree>::node_descriptor node_descriptor;

  treemap_geometric(const Tree& tree,
		    TotalWeightMap twm,
		    Map xm,
		    Map ym,
		    Drawer drawer = Drawer())
    : tree_(tree), total_weight_(twm),
      xm_(xm), ym_(ym),
      drawer_(drawer)
  { }
  void start() { drawer_.start(); }
  void finish() { drawer_.finish(); }

  unsigned visit(const box_type& box,
		 node_descriptor n,
		 unsigned depth = 0)
  {
    if (! drawer_.begin_box(box,n,tree_,depth)) return 0;
    box_type b(box);
    unsigned ret = 1;
    drawer_.draw_border(b, n, tree_, depth);
    if (is_leaf(n,tree_)) {
      drawer_.draw_box(b, n, tree_, depth);
    }
    else {
      children_iterator i, end;
      tie(i,end) = children(n, tree_);
      int size = degree(n, tree_);

      std::vector<node_descriptor> x_order(i, end);
      std::vector<node_descriptor> y_order(i, end);
      std::sort(x_order.begin(), x_order.end(), indirect_compare(x_map_));
      std::sort(y_order.begin(), y_order.end(), indirect_compare(y_map_));

      
    }
    drawer_.end_box(box,n,tree_,depth);
    return ret;
  }
    
};
} // namespace infovis

#endif // INFOVIS_TREE_TREEMAP_GEOMETRIC_HPP
