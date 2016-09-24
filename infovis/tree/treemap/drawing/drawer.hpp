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
#ifndef INFOVIS_TREE_TREEMAP_DRAWING_DRAWER_HPP
#define INFOVIS_TREE_TREEMAP_DRAWING_DRAWER_HPP

#include <infovis/tree/tree_traits.hpp>
#include <infovis/drawing/box.hpp>
#include <infovis/drawing/direction.hpp>

namespace infovis {

/**
 * Minimal drawer.
 */
template <class Tree, class Box>
struct null_drawer {

  void start() { }
  void finish() { }

  void begin_strip(const Box& b,
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth,
		   direction dir) { }
  void end_strip(const Box& b,
		 typename tree_traits<Tree>::node_descriptor n,
		 unsigned depth,
		 direction dir) { }
  bool begin_box(const Box& b,
		 typename tree_traits<Tree>::node_descriptor n,
		 unsigned depth) { return true; }
  void draw_box(const Box& b,
		typename tree_traits<Tree>::node_descriptor n,
		unsigned depth) { }
  void draw_border(Box& b, 
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth) { }
  void remove_border(Box& b, 
		     typename tree_traits<Tree>::node_descriptor n,
		     unsigned depth) { }
  void end_box(const Box& b, 
	       typename tree_traits<Tree>::node_descriptor n,
	       unsigned depth) { }
};

} // namespace infovis

#endif // INFOVIS_TREE_TREEMAP_DRAWING_DRAWER_HPP
