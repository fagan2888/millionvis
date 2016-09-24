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
#ifndef INFOVIS_TREE_TREEMAP_DRAWING_DEBUG_DRAWER_HPP
#define INFOVIS_TREE_TREEMAP_DRAWING_DEBUG_DRAWER_HPP

#include <infovis/tree/treemap/drawing/drawer.hpp>
#include <iostream>

namespace infovis {

template <class Tree, class Box, class Drawer>
struct debug_drawer : public Drawer
{
  enum State {
    drawer_inited,
    drawer_started,
    drawer_visiting,
    drawer_finished
  };
#ifndef NDEBUG
  State state;
#endif

  debug_drawer() : Drawer() {
#ifndef NDEBUG
    state = drawer_inited;
#endif
  }
  debug_drawer(const Drawer& d) : Drawer(d) {
#ifndef NDEBUG
    state = drawer_inited;
#endif
  }
  
  void start() {
#ifndef NDEBUG
    if (state != drawer_inited &&
	state != drawer_finished) {
      std::cerr << "Incorrect state in Drawer::start\n";
    }
    state = drawer_started;
#endif
    Drawer::start();
  }
  void finish() {
#ifndef NDEBUG
    if (state != drawer_started &&
	state != drawer_visiting) {
      std::cerr << "Incorrect state in Drawer::finish\n";
    }
    state = drawer_finished;
#endif
    Drawer::finish();
  }

  bool begin_box(const Box& b,
		 typename tree_traits<Tree>::node_descriptor n,
		 unsigned depth) {
#ifndef NDEBUG
    if (state != drawer_started &&
	state != drawer_visiting) {
      std::cerr << "Incorrect state in Drawer::begin_box\n";
    }
    state = drawer_visiting;
#endif
    return Drawer::begin_box(b, n, depth);
  }
  void draw_box(const Box& b,
		typename tree_traits<Tree>::node_descriptor n,
		unsigned depth) {
    Drawer::draw_box(b, n, depth);
  }
  void draw_border(Box& b, 
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth) {
    Drawer::draw_border(b, n, depth);
  }
  void remove_border(Box& b, 
		     typename tree_traits<Tree>::node_descriptor n,
		     unsigned depth) {
    Drawer::remove_border(b, n, depth);
  }
  void end_box(const Box& b, 
	       typename tree_traits<Tree>::node_descriptor n,
	       unsigned depth) {
    Drawer::end_box(b, n, depth);
  }
};
} // namespace infovis

#endif // INFOVIS_TREE_TREEMAP_DRAWING_DEBUG_DRAWER_HPP
