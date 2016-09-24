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
#ifndef INFOVIS_TREE_CONCEPTS_HPP
#define INFOVIS_TREE_CONCEPTS_HPP

#include <infovis/alloc.hpp>
#include <boost/config.hpp>
#include <infovis/tree/tree_traits.hpp>
#include <boost/property_map.hpp>
#include <boost/concept_check.hpp>

namespace infovis {

/**
 * Concept (abstract requirements) for a tree data structure.
 *
 * A tree should provide the following information:
 * - a node_descriptor type for representing a node
 * - a children_iterator type for iterating over the children of a node
 * - a degree_size_type type for holding the degree of a node
 * - a root(tree) and tree::nil() method to return the root node
 * - a children(node) method to get the children iterator for a node
 * - a degree(node) method to get the degree of a node
 * - a is_leaf(node) method to test whether a node is a leaf (degree==0)
 *
 * Furthermore, it should implement the following concepts:
 * - the node_descriptor should implement the DefaultConstructibleConcept
 * - the node_descriptor should implement the EqualityComparableConcept
 * - the node_descriptor should implement the AssignableConcept
 * - the children_iterator should implement the ForwardIteratorConcept
 */
template <class T>
struct TreeConcept
{
  /// tree_traits<T> should define a node_descriptor type
  typedef typename tree_traits<T>::node_descriptor node_descriptor;

  /// tree_traits<T> should define a children_iterator type
  typedef typename tree_traits<T>::children_iterator children_iterator;    

  /// Check the constraints of the tree type.
  void constraints() {
    boost::function_requires< boost::DefaultConstructibleConcept<node_descriptor> >();
    boost::function_requires< boost::EqualityComparableConcept<node_descriptor> >();
    boost::function_requires< boost::AssignableConcept<node_descriptor> >();
    boost::function_requires< boost::ForwardIteratorConcept<children_iterator> >();

    n = tree_traits<T>::nil();
    n = *p.first;
    const_constraints(t);
  }

  /// Check the constraints of a constant tree type.
  void const_constraints(const T& t) {
    n = root(t);
    p = children(n, t);
    d = degree(n, t);
    if (is_leaf(n, t))
      n = *p.first;
  }

  std::pair<children_iterator, children_iterator> p;
  typename tree_traits<T>::node_descriptor n;
  typename tree_traits<T>::degree_size_type d;
  T t;
};

/**
 * Concept (Abstract requirements) for a tree maintaining parents information
 *
 * A ParentedTreeConcept should implement the TreeConcept and provide
 * the parent(node) method.
 */
template <class T>
struct ParentedTreeConcept
{
  void constraints() {
    boost::function_requires< TreeConcept<T> >();
    n = parent(n, t);
  }
  void const_constraints(const T& t) {
    n = parent(n, t);
  }
  typename tree_traits<T>::node_descriptor n;
  T t;
};

/**
 * Concept (Abstract requirements) for a tree maintaining a list of all its nodes.
 *
 * A NodeListTreeConcept implements the TreeConcept and requires an
 * iterator type node_iterator to iterator over all the nodes of the
 * tree, and the methods nodes(const tree&) to get the first and last
 * iterator, as well as the method num_nodes(const tree&) to get the
 * count of nodes in the tree.
 */
template <class T>
struct NodeListTreeConcept
{
  typedef typename tree_traits<T>::node_iterator node_iterator;
  typedef typename tree_traits<T>::nodes_size_type nodes_size_type;

  void constraints() {
    boost::function_requires< TreeConcept<T> >();
    boost::function_requires< boost::InputIteratorConcept<node_iterator> >();

    p = nodes(t);
    n = *(p.first);
    const_constraints(t);
  }
  void const_constraints(const T& t) {
    p = nodes(t);
    n = *(p.first);
    N = num_nodes(t);
  }
  std::pair<node_iterator,node_iterator> p;
  typename tree_traits<T>::node_descriptor n;
  T t;
  nodes_size_type N;
};

/**
 * Concept (Abstract requirements) for a tree that can be built
 * dynamically.
 *
 * A BuildableTreeConcept implements the TreeConcept and requires a
 * method add_node(node_descriptor n, table& t) that returns a new
 * node from a parent node and a tree.
 */
template <class T>
struct BuildableTreeConcept
{
  void constraints() {
    boost::function_requires< TreeConcept<T> >();
    n = add_node(n, t);
  }
  typename tree_traits<T>::node_descriptor n;
  T t;
};

/// Concept (Abstract requirements) for a tree that can be dynamically modified
template <class T>
struct MutableTreeConcept
{
  void constraints() {
    boost::function_requires< BuildableTreeConcept<T> >();
    remove_node(n, t);
    clear_node(n, t);
  }
  typename tree_traits<T>::node_descriptor n;
  T t;
};
} // namespace infovis

#endif
