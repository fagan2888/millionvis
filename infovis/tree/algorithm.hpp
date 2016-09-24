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
#ifndef INFOVIS_TREE_ALGORITHM
#define INFOVIS_TREE_ALGORITHM

#include <infovis/alloc.hpp>
#include <infovis/tree/tree_traits.hpp>
#include <infovis/tree/visitor.hpp>
#include <infovis/tree/tree_concepts.hpp>
#include <vector>
#include <functional>

namespace infovis {

struct true_copier_pred {
  template <class InNode>
  bool operator()(InNode) { return true; }
};
struct null_copier {
  template <class InNode, class OutNode>
  void operator()(InNode, OutNode) { }
};

/**
 * Visitor for copying a tree.
 */
template <class InTree, class OutTree,
	  class NodeCopier = null_copier, class Pred = true_copier_pred >
struct copy_tree_visitor
{
  typedef typename tree_traits<InTree>::node_descriptor in_node_descriptor;
  typedef typename tree_traits<OutTree>::node_descriptor out_node_descriptor;
  const InTree& in_;
  OutTree& out_;
  NodeCopier copier_;
  Pred pred_;
  std::vector<out_node_descriptor, gc_alloc<out_node_descriptor> > node_stack;

  out_node_descriptor current() const {
    return node_stack.back();
  }
  out_node_descriptor push() {
    out_node_descriptor n = add_node(current(), out_);
    node_stack.push_back(n);
    return n;
  }
  void pop() {
    node_stack.pop_back();
  }

  copy_tree_visitor(const InTree& in, OutTree& out,
		    NodeCopier copier = NodeCopier(),
		    Pred pred = Pred())
    : in_(in), out_(out), copier_(copier), pred_(pred) {
    boost::function_requires< TreeConcept<InTree> > ();
    boost::function_requires< BuildableTreeConcept<OutTree> > ();
    node_stack.push_back(tree_traits<OutTree>::nil());
  }

  bool preorder(in_node_descriptor in) {
    if (pred_(in)) {
      out_node_descriptor out = push();
      copier_(in, out);
      return true;
    }
    return false;
  }
  void inorder(in_node_descriptor) { }
  void postorder(in_node_descriptor) {
    pop();
  }
};

template <class InNode, class OutNode, class Assoc>
struct permutation_recorder :
    public std::binary_function<InNode,OutNode,void>
{
  Assoc assoc;
  void operator()(InNode in, OutNode out) {
    assoc[in] = out;
  }
};

template <class InNode, class OutNode, class Copier1, class Copier2>
struct compose_copier
{
  Copier1 c1;
  Copier2 c2;
  void operator()(InNode in, OutNode out) {
    c1(in,out);
    c2(in,out);
  }
};  

template <class InTree, class OutTree, class NodeCopier>
inline void
copy_tree(const InTree& in, OutTree& out, NodeCopier copier)
{
  copy_tree_visitor<InTree,OutTree,NodeCopier> vis(in, out, copier);
  traverse_tree(root(in), in, vis);
}

template <class InTree, class OutTree, class NodeCopier, class Pred>
inline void
copy_tree_if(const InTree& in, OutTree& out, NodeCopier copier, Pred pred)
{
  copy_tree_visitor<InTree,OutTree,NodeCopier> vis(in, out, copier, pred);
  traverse_tree(root(in), in, vis);
}

template <class InTree, class OutTree, class NodeCopier, class Pred>
inline void
copy_tree_prune_if(const InTree& in, OutTree& out, NodeCopier copier, Pred pred)
{
  copy_tree_visitor<InTree,OutTree,NodeCopier,Pred> vis(in, out, copier, pred);
  search_tree(root(in), in, vis);
}


struct max_depth_visitor
{
  unsigned depth;
  unsigned max_depth;
  max_depth_visitor() : depth(0), max_depth(0) { }
  
  template <class Node> void preorder(Node) {
    depth++;
    if (depth > max_depth)
      max_depth = depth;
  }
  template <class Node> void inorder(Node) { }
  template <class Node> void postorder(Node) {
    depth--;
  }
};

template <class Tree>
inline unsigned depth(const Tree& t)
{
  max_depth_visitor visitor;
  traverse_tree(root(t), t, visitor);
  return visitor.max_depth;
}
  
} // namespace infovis

#endif // INFOVIS_TREE_ALGORITHM
