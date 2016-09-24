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
#ifndef INFOVIS_TREE_BFS_VISITOR_HPP
#define INFOVIS_TREE_BFS_VISITOR_HPP

#include <infovis/alloc.hpp>
#include <boost/pending/queue.hpp>
#include <infovis/tree/visitor.hpp>

namespace infovis {

/**
 * Breadth first search visitor concept
 */
template <class Visitor, class Tree>
struct TreeBFSVisitorConcept {
  void constraints() {
    boost::function_requires< boost::CopyConstructibleConcept<Visitor> >();
    vis.initialize_node(n, t);
    bool v = vis.discover_node(n, t);
    vis.examine_node(n, t);
    vis.finish_node(n, t);
  }
  Visitor vis;
  Tree t;
  typename tree_traits<Tree>::node_descriptor n;
};
  
/**
 * Default breadth first search visitor, doing nothing.
 */
struct null_bfs_visitor {
  template <class Tree>
  void initialize_node(typename tree_traits<Tree>::node_descriptor n,
		       const Tree& t) { }
    
  template <class Tree>
  bool discover_node(typename tree_traits<Tree>::node_descriptor n,
		     const Tree& t) { return true; }

  template <class Tree>
  void examine_node(typename tree_traits<Tree>::node_descriptor n,
		    const Tree& t) { }

  template <class Tree>
  void finish_node(typename tree_traits<Tree>::node_descriptor n,
		   const Tree& t) { }
    
};

/**
 * Method to visit a tree using a breadth first search traversal.
 * @param n the starting node
 * @param t the tree
 * @param vis the Breadth first search visitor
 * @param Q a Buffer for holding nodes.
 */
template <class Tree, class BFSVisitor, class Buffer>
void bfs_visit(typename tree_traits<Tree>::node_descriptor n,
	       const Tree& t,
	       BFSVisitor vis, Buffer& Q)
{
  boost::function_requires< TreeConcept<Tree> >();
  boost::function_requires< TreeBFSVisitorConcept<BFSVisitor,Tree> >();
  typedef tree_traits<Tree> TTraits;
  typedef typename TTraits::node_descriptor node;

  if (vis.discover_node(n, t))
    Q.push(n);
  while (! Q.empty()) {
    node u = Q.top();
    Q.pop();
    vis.examine_node(u, t);
    typename TTraits::children_iterator i, end;
    for (boost::tie(i, end) = children(u, t); i != end; i++) {
      node v = *i;
      if (vis.discover_node(v, t))
	Q.push(v);
    }	// for
    vis.finish_node(n, t);
  } // while
}

/**
 * Method to visit a tree using a breadth first search traversal.
 * @param n the starting node
 * @param t the tree
 * @param vis the Breadth first search visitor
 */
template <class Tree, class BFSVisitor>
void bfs_visit(typename tree_traits<Tree>::node_descriptor n,
	       const Tree& t,
	       BFSVisitor vis)
{
  typedef boost::queue<tree_traits<Tree>::node_descriptor> Buffer;
  Buffer Q;
  bfs_visit(n, t, vis, Q);
}

/**
 * Method to search a tree using a breadth first search traversal.
 * @param n the starting node
 * @param t the tree
 * @param vis the Breadth first search visitor
 * @param Q a Buffer for holding nodes.
 */
template <class Tree, class BFSVisitor, class Buffer >
void bfs_search(typename tree_traits<Tree>::node_descriptor n,
		const Tree& t,
		BFSVisitor vis, Buffer& Q)
{
  typename tree_traits<Tree>::node_iterator i, end;
  for (tie(i, end) = nodes(t); i != end; i++) {
    vis.initialize_node(*i, t);
  }
  bfs_visit(t, n, Q, vis);
}

/**
 * Method to search a tree using a breadth first search traversal.
 * @param n the starting node
 * @param t the tree
 * @param vis the Breadth first search visitor
 */
template <class Tree, class BFSVisitor>
void bfs_search(typename tree_traits<Tree>::node_descriptor n,
		const Tree& t,
		BFSVisitor vis)
{
  typedef typename boost::queue<typename tree_traits<Tree>::node_descriptor> Buffer;
  Buffer Q;
  bfs_search(n, t, vis, Q);
}


} // namespace infovis 

#endif // INFOVIS_TREE_BFS_VISITOR_HPP
