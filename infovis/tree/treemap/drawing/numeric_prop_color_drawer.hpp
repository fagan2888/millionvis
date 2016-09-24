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
#ifndef INFOVIS_TREE_TREEMAP_DRAWING_NUMERIC_PROP_COLOR_DRAWER_HPP
#define INFOVIS_TREE_TREEMAP_DRAWING_NUMERIC_PROP_COLOR_DRAWER_HPP

#include <infovis/drawing/drawing.hpp>
#include <infovis/tree/property_tree.hpp>

namespace infovis {

/**
 * Sample color drawer using the a numeric property
 */
struct numeric_prop_color_drawer
{
  typedef property_tree Tree;
  typedef tree_traits<Tree>::node_descriptor node_descriptor;
  const Tree::numeric_prop * color_prop;
  

  numeric_prop_color_drawer()
    : color_prop(0) { }

  void set_color_prop(const property_tree::numeric_prop * c) {
    color_prop = c;
  }

  const Color& operator() (node_descriptor n,
			   unsigned depth) const {
    int code = int((*color_prop)[n]);
    switch(code) {
    case 1:
    case 2: return (color_white);
    case 3: return (color_red);
    case 4: return(color_green);
    case 5: return (color_blue);
    case 6: return(color_cyan);
    case 7: return(color_magenta);
    case 8: return(color_yellow);
    default: return color_half_grey;
    }
  }
};

} // namespace infovis

#endif // INFOVIS_TREE_TREEMAP_DRAWING_NUMERIC_PROP_COLOR_DRAWER_HPP
