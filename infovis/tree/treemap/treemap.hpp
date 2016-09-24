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
#ifndef INFOVIS_TREE_TREEMAP_TREEMAP_HPP
#define INFOVIS_TREE_TREEMAP_TREEMAP_HPP

#include <infovis/alloc.hpp>
#include <boost/config.hpp>
#include <infovis/tree/tree_traits.hpp>
#include <infovis/tree/tree_concepts.hpp>
#include <infovis/table/filter.hpp>
#include <infovis/tree/sum_weight_visitor.hpp>
#include <infovis/tree/treemap/drawing/drawer.hpp>

namespace infovis {

/**
 * Base treemap class.
 */
template <class Tree,
	  class Box,
	  class WeightMap,
	  class Drawer = null_drawer<Tree,Box>,
	  class Filter = filter_none
>
struct treemap
{
  typedef Box box_type;
  typedef typename box_traits<Box>::coord_type coord_type;
  typedef typename box_traits<Box>::dist_type dist_type;
  typedef typename tree_traits<Tree>::children_iterator children_iterator;
  typedef typename tree_traits<Tree>::node_descriptor node_descriptor;
    
  treemap(const Tree& tree,
	  WeightMap wm,
	  Drawer drawer = Drawer(),
	  Filter filter = Filter())
    : tree_(tree),
      weight_(wm),
      drawer_(drawer),
      filter_(filter)
  { }

  void start() { drawer_.start(); }
  void finish() { drawer_.finish(); }

  const Tree& tree_;
  WeightMap weight_;
  Drawer drawer_;
  Filter filter_;
};

} // namespace infovis

#endif // INFOVIS_TREE_TREEMAP_TREEMAP_HPP

