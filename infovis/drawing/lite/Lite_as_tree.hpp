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
#ifndef INFOVIS_DRAWING_LITE_LITE_AS_TREE_HPP
#define INFOVIS_DRAWING_LITE_LITE_AS_TREE_HPP

#include <infovis/drawing/lite/Lite.hpp>
#include <infovis/tree/tree_traits.hpp>

namespace infovis {

/**
 * Specialize tree_traits to handle a tree of lite as a tree.
 */
template<>
struct tree_traits<const Lite*>
{
  typedef const Lite* node_descriptor;    
  typedef Lite::const_iterator children_iterator;    
  typedef Lite::List::size_type degree_size_type;
  static node_descriptor nil() { return 0; }
};

inline tree_traits< const Lite* >::node_descriptor
root(const Lite * t)
{
  return t;
}

inline std::pair< tree_traits< const Lite* >::children_iterator,
		  tree_traits< const Lite* >::children_iterator>
children(tree_traits< const Lite* >::node_descriptor n, const Lite*)
{
  return
    std::pair<
    tree_traits< const Lite* >::children_iterator,
    tree_traits< const Lite* >::children_iterator
    >(n->begin(), n->end());
}

inline tree_traits< const Lite* >::degree_size_type
degree(tree_traits< const Lite* >::node_descriptor n,
       const Lite*)
{
  return n->childCount();
}

inline bool
is_leaf(tree_traits< const Lite* >::node_descriptor n,
       const Lite* l)
{
  return degree(n, l);
}

} // namespace infovis
#endif // INFOVIS_DRAWING_LITE_LITE_AS_TREE_HPP
