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
//  (C) Copyright Jeremy Siek 1999. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

#ifndef INFOVIS_TREE_TRAITS_HPP
#define INFOVIS_TREE_TRAITS_HPP

#include <infovis/alloc.hpp>
#include <boost/config.hpp>
#include <boost/tuple/tuple.hpp>

namespace infovis {

/**
 * Traits of a tree.
 * This class is the default set of types and static methods a tree
 * structure should offer to be usable to all the algorithms.
 */
template <class T>
struct tree_traits {
  typedef  typename T::node_descriptor node_descriptor; /// Type to reference a node.
  typedef typename T::children_iterator children_iterator; /// Type to reference an iterator over the children of a node
  typedef typename T::degree_size_type degree_size_type; /// Type for the degree of nodes
  static node_descriptor nil() { return T::nil(); } /// static method to access the value of the root of the tree
};

} /* namespace infovis */

#endif /* INFOVIS_TREE_TRAITS_HPP */
