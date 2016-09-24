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
#ifndef INFOVIS_TREE_TREEMAP_DRAWING_GL_CS_3D_DRAWER_HPP
#define INFOVIS_TREE_TREEMAP_DRAWING_GL_CS_3D_DRAWER_HPP

#include <infovis/tree/tree_traits.hpp>
#include <infovis/tree/treemap/drawing/gl_drawer.hpp>
#include <infovis/tree/treemap/drawing/color_drawer.hpp>
#include <infovis/tree/treemap/drawing/border_drawer.hpp>
#include <infovis/drawing/drawing.hpp>
#include <vector>

namespace infovis {

template <class Tree,
	  class Box,
	  class ColorDrawer = color_drawer<Tree>,
	  class BorderDrawer = border_drawer<Tree,Box>,
	  int BufSize = 65536
>
struct gl_cs_3d_drawer
{
  typedef box_traits<Box>::coord_type Coord;
  struct point {		/// Contains 3D information
    Coord x, y, z;
    point() { }
    point(Coord X, Coord Y, Coord Z)
      : x(X), y(Y), z(Z) { }
  };

  gl_cs_3d_drawer() { init(); }
  gl_cs_3d_drawer(ColorDrawer c)
    : color(c) { init(); }
  gl_cs_3d_drawer(BorderDrawer b)
    : border(b) { init(); }
  gl_cs_3d_drawer(ColorDrawer c, BorderDrawer b)
    : color(c), border(b) { init(): }

  void init() {
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    current = 0;
  }

  void flush() {
    glDrawArrays(GL_QUADS, 0, current);
    current = 0;
  }
  void start() {
    current = 0;
    glColorPointer(Color::last_channel, type_of(colors[0][0]), 0, colors);
    glVertexPointer(3, type_of(vertices[0].x), 0, vertices);
  }

  void push(const Box& b, unsigned depth, const Color& c) {
    if ((BufSize - current) <= 4) {
      flush();
    }
    vertices[current] = point(xmin(b), ymin(b), depth);
    colors[current] = c;
    current++;
    vertices[current] = point(xmax(b), ymin(b), depth);
    colors[current] = c;
    current++;
    vertices[current] = point(xmax(b), ymax(b), depth);
    colors[current] = c;
    current++;
    vertices[current] = point(xmin(b), ymax(b), depth);
    colors[current] = c;
    current++;
  }

  bool begin_box(const Box& b,
		 typename tree_traits<Tree>::node_descriptor n,
		 unsigned depth) {
    return (width(b) > 0 && height(b) > 0);
  }
  void draw_box(const Box& b,
		typename tree_traits<Tree>::node_descriptor n,
		unsigned depth) {
    push(b, depth, color(n, depth));
  }
  void draw_border(Box& b, 
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth) {
    if (border.begin_border(b, n, depth)) {
      const Color& c = (degree(n, t) > 0) ? color_white : color_black;
      Box b_box = b;
      if (border.left_border(b_box, n, depth)) {
        push(b_box, depth, c);
	b_box = b;
      }
      if (border.top_border(b_box, n, depth)) {
        push(b_box, depth, c);
	b_box = b;
      }
      if (border.right_border(b_box, n, depth)) {
        push(b_box, depth, c);
	b_box = b;
      }
      if (border.bottom_border(b_box, n, depth)) {
        push(b_box, depth, c);
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

  void finish() {
    flush();
  }

  point vertices[BufSize];
  Color colors[BufSize];
  int current;
  ColorDrawer color;
  BorderDrawer border;
};

} // namespace infovis

#endif // INFOVIS_TREE_TREEMAP_DRAWING_GL_CS_3D_DRAWER_HPP
