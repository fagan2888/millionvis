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
#ifndef INFOVIS_TREE_VISITOR_HPP
#define INFOVIS_TREE_VISITOR_HPP

#include <infovis/alloc.hpp>
#include <infovis/tree/tree_traits.hpp>
#include <infovis/tree/tree_concepts.hpp>

namespace infovis {

/**
 * Method for traversing a tree that implements the TreeConcept.
 *
 * @param v a node
 * @param t a tree
 * @param visitor a TreeVisitor (@see null_tree_visitor)
 */
template <class Tree, class TreeVisitor>
void traverse_tree(typename tree_traits<Tree>::node_descriptor v,
		   const Tree& t, TreeVisitor& visitor)
{
  boost::function_requires< TreeConcept<Tree> > ();
  visitor.preorder(v);
  typedef typename tree_traits<Tree>::children_iterator children_iterator;
  children_iterator i, end;
  std::pair<children_iterator,children_iterator> p = children(v,t);
  boost::tie(i, end) = children(v, t);
  if (i != end) {
    traverse_tree(*i++, t, visitor);
    visitor.inorder(v);
    while (i != end)
      traverse_tree(*i++, t, visitor);
  } else
    visitor.inorder(v);
  visitor.postorder(v);
}

/**
 * The simplest tree visitor.
 *
 * A tree visitor should implment three methods:
 * - preorder(Node)
 * - inorder(Node)
 * - postorder(Node).
 */
struct null_tree_visitor {
  /**
   * Called when initially entering the node in a depth first traversal
   */
  template <class Node> void preorder(Node) { }
  /**
   * Called after some children of the node have been visited in a
   * depth first traversal.
   */
  template <class Node> void inorder(Node) { }
  /**
   * Called after the children of the node have been visited in a
   * depth first traversal.
   */
  template <class Node> void postorder(Node) { }
};

template <class Tree, class TreeSearcher>
void search_tree(typename tree_traits<Tree>::node_descriptor v,
		 const Tree& t, TreeSearcher& searcher)
{
  boost::function_requires< TreeConcept<Tree> > ();
  if (searcher.preorder(v)) {
    typedef typename tree_traits<Tree>::children_iterator children_iterator;
    children_iterator i, end;
    std::pair<children_iterator,children_iterator> p = children(v,t);
    tie(i, end) = children(v, t);
    if (i != end) {
      search_tree(*i++, t, searcher);
      searcher.inorder(v);
      while (i != end)
	search_tree(*i++, t, searcher);
    } else
      searcher.inorder(v);
    searcher.postorder(v);
  }
}

/**
 * Visitor for searching
 */ 
struct null_tree_searcher {
  template <class Node> bool preorder(Node) { return true; }
  template <class Node> void inorder(Node) { }
  template <class Node> void postorder(Node) { }
};



} // namespace infovis

#endif // INFOVIS_TREE_VISITOR_HPP
