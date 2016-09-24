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
#ifndef INFOVIS_TREE_TREEMAP_DRAWING_COLOR_DRAWER_HPP
#define INFOVIS_TREE_TREEMAP_DRAWING_COLOR_DRAWER_HPP

#include <infovis/drawing/drawing.hpp>
#include <infovis/tree/tree_traits.hpp>

namespace infovis {

/**
 * Default drawer for drawing different colors.
 */ 
template <class Tree>
struct color_drawer {
  const Color& operator()(typename tree_traits<Tree>::node_descriptor n,
			  unsigned depth) const {
    switch(depth % 6) {
    case 0:
      return color_red;
      break;
    case 1:
      return color_green;
      break;
    case 2:
      return color_blue;
      break;
    case 3:
      return color_cyan;
      break;
    case 4:
      return color_magenta;
      break;
    case 5:
      return color_yellow;
      break;
    }
    return color_half_grey;		// will not happen
  }
};

} // namespace infovis

#endif // INFOVIS_TREE_TREEMAP_DRAWING_COLOR_DRAWER_HPP
