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
#ifndef INFOVIS_TREE_TREEMAP_DRAWING_GL_DRAWER_HPP
#define INFOVIS_TREE_TREEMAP_DRAWING_GL_DRAWER_HPP

#include <infovis/tree/tree_traits.hpp>
#include <infovis/tree/treemap/drawing/drawer.hpp>
#include <infovis/tree/treemap/drawing/color_drawer.hpp>
#include <infovis/tree/treemap/drawing/border_drawer.hpp>
#include <infovis/drawing/box.hpp>
#include <infovis/drawing/gl_support.hpp>

namespace infovis {

/**
 * Drawer using OpenGL
 */
template <class Tree, class Box,
	  class ColorDrawer = color_drawer<Tree>,
	  class BorderDrawer = border_drawer<Tree, Box>
>
struct gl_drawer : public null_drawer<Tree,Box>
{
  ColorDrawer color;
  BorderDrawer border;

  void start() { }
  void finish() { }
  bool begin_box(const Box& b,
		 typename tree_traits<Tree>::node_descriptor n,
		 unsigned depth) {
    return (width(b) > 0) && (height(b) > 0);
  }
  void draw_box(const Box& b,
		typename tree_traits<Tree>::node_descriptor n,
		unsigned depth) {
    infovis::set_color(color(n, depth));
    infovis::draw_box(b);
  }
  void draw_border(Box& b, 
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth) {
    if (border.begin_border(b, n, depth)) {
      set_color(color_black);
      Box b_box = b;
      if (border.left_border(b_box, n, depth)) {
	infovis::draw_box(b_box);
	b_box = b;
      }
      if (border.top_border(b_box, n, depth)) {
	infovis::draw_box(b_box);
	b_box = b;
      }
      if (border.right_border(b_box, n, depth)) {
	infovis::draw_box(b_box);
	b_box = b;
      }
      if (border.bottom_border(b_box, n, depth)) {
	infovis::draw_box(b_box);
      }
      border.remaining_box(b, n, depth);
    }
  }
  void remove_border(Box& b, 
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth) {
    if (border.begin_border(b, n, depth)) {
      border.remaining_box(b, n, depth);
    }
  }
  void end_box(const Box& b, 
	       typename tree_traits<Tree>::node_descriptor n,
	       unsigned depth) { }
};

} // namespace infovis

#endif // INFOVIS_TREEMAP_DRAWING_DRAWER_HPP
