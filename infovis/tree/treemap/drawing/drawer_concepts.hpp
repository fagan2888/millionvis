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
#ifndef INFOVIS_TREE_TREEMAP_DRAWING_DRAWER_CONCEPTS_HPP
#define INFOVIS_TREE_TREEMAP_DRAWING_DRAWER_CONCEPTS_HPP

#include <infovis/alloc.hpp>
#include <infovis/drawing/box_concepts.hpp>
#include <infovis/tree/tree_concepts.hpp>

namespace infovis {

/**
 * Concept (abstract requirements) for a treemap
 */
template <class Tree, class Box>
struct TreemapDrawerConcept
{
  typedef typename tree_traits<Tree>::node_descriptor node_descriptor;
  typedef typename tree_traits<Tree>::children_iterator children_iterator;    

  void constraints() {
    function_requires<TreeConcept<Tree> >();
    function_requires<BoxConcept<Box> >();

    start();
    begin_box(b, n, depth);
    begin_strip(b, n, depth);
    end_strip(b, n, depth);
    draw_box(b, n, depth);
    draw_border(vb, n, depth);
    remove_border(vb, n, depth);
    end_box(b, n, depth);
    finish();
  }

  const Box b;
  Box vb;
  node_descriptor n;
  const Tree t;
  unsigned depth;
};

} // namespace infovis


#endif // INFOVIS_TREE_TREEMAP_DRAWING_DRAWER_CONCEPTS_HPP
