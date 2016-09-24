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
#ifndef INFOVIS_TREE_SUM_WEIGHT_VISITOR_HPP
#define INFOVIS_TREE_SUM_WEIGHT_VISITOR_HPP

#include <infovis/alloc.hpp>
#include <infovis/tree/tree_traits.hpp>
#include <infovis/tree/visitor.hpp>
#include <vector>

namespace infovis {

/**
 * Recursively compute the sum of the values of the children and store
 * in into the parent
 */
template <class Tree, class WeightMap>
struct sum_weight_visitor
{
  const Tree& tree_;
  WeightMap& weight_;
  typedef typename tree_traits<Tree>::node_descriptor node_descriptor;
  typedef typename tree_traits<Tree>::children_iterator children_iterator;

  sum_weight_visitor(const Tree& t, WeightMap& w)
    : tree_(t), weight_(w) { }

  void preorder(node_descriptor n) {}
  void inorder(node_descriptor n) {
  }
  void postorder(node_descriptor n) {
    if (! is_leaf(n, tree_)) {
      weight_[n] = 0;
      children_iterator i, e;
      boost::tie(i, e) = children(n, tree_);
      while (i != e) {
	weight_[n] += weight_[*i];
	++i;
      }
    }
  }
};

/**
 * Compute the sum of the weights in place.
 * @param t a tree
 * @param weights a column
 */
template <class Tree, class WeightMap>
void sum_weights(const Tree& t,
		 WeightMap& weight)
{
  sum_weight_visitor<Tree,WeightMap> vis(t, weight);
  traverse_tree(root(t), t, vis);
}

template <class Tree, class WeightMap>
struct test_sum_weight_visitor
{
  const Tree& tree_;
  WeightMap& weight_;
  typedef typename tree_traits<Tree>::node_descriptor node_descriptor;
  typedef typename tree_traits<Tree>::children_iterator children_iterator;

  test_sum_weight_visitor(const Tree& t, WeightMap& w)
    : tree_(t), weight_(w) { }

  void preorder(node_descriptor n) {}
  void inorder(node_descriptor n) {
  }
  void postorder(node_descriptor n) {
    if (! is_leaf(n, tree_)) {
      float sum = 0;
      children_iterator i, e;
      tie(i, e) = children(n, tree_);
      while (i != e) {
	sum += weight_[*i];
	++i;
      }
      if (sum != weight_[n])
	throw false;
    }
  }
};

template <class Tree, class WeightMap>
bool test_sum_weights(const Tree& t,
		      WeightMap& weight)
{
  test_sum_weight_visitor<Tree,WeightMap> vis(t, weight);
  try {
    traverse_tree(root(t), t, vis);
  }
  catch (bool b) {
    return b;
  }
  return true;
}

} // namespace infovis

#endif // INFOVIS_TREE_SUM_WEIGHT_VISITOR_HPP
