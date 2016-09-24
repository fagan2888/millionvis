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

#include <infovis/tree/vector_as_tree.hpp>
#include <infovis/tree/treemap_slice_and_dice.hpp>
#include <boost/directory.h>
#include <iostream>

using namespace infovis;

struct PrintVisitor {
  typedef std::vector<std::string,gc_alloc<std::string> > StringList;
  const StringList& names;
  int indent;

  PrintVisitor(const StringList& n) : names(n), indent(0) {}

  static void tab(int i) {
    while (i-- != 0)
      std::cout << ' ';
  }
  void preorder(tree_traits< vector_as_tree>::node_descriptor n) {
    //tab(indent);
    indent++;
    //std::cout << "preorder " << names[n] << "\n";
  }
  void inorder(tree_traits< vector_as_tree>::node_descriptor n) {
    //tab(indent);
    //std::cout << "inorder " << names[n] << "\n";
  }
  void postorder(tree_traits< vector_as_tree>::node_descriptor n) {
    tab(indent--);
    std::cout << "postorder " << names[n] << "\n";
  }
};

typedef std::vector<float,gc_alloc<float, true> > WeightMap;

static void build_tree(tree_traits< vector_as_tree >::node_descriptor parent,
		       vector_as_tree& tree, const std::string& dirname,
		       std::vector<std::string,gc_alloc<std::string> >& names,
		       WeightMap& wm)
{
  using namespace infovis::filesystem;
  //std::cout << "entering " << dirname << std::endl;
  for (dir_it it(dirname); it != dir_it(); ++it) {
    if ((*it)[0] == '.')
      continue;
    tree_traits< vector_as_tree >::node_descriptor n = add_node(parent, tree);
    names.push_back(*it);
    wm.push_back(get<size>(it));
    if (get<is_directory>(it))
      build_tree(n, tree, dirname+"/"+(*it), names, wm);
  }
  //std::cout << "leaving " << dirname << std::endl;
}

int main(int argc, char * argv[])
{
  tree_traits< vector_as_tree >::node_descriptor n;
  tree_traits< vector_as_tree >::children_iterator p;
  std::vector<std::string,gc_alloc<std::string> > names;
  WeightMap wm;

  vector_as_tree t;
  add_node(root(t), t);
  wm.push_back(0);
  
  if (argc == 1) {
    names.push_back(".");
    build_tree(root(t), t, ".", names, wm);
  }
  else {
    names.push_back(argv[1]);
    build_tree(root(t), t, argv[1], names, wm);
  }
  
  traverse_tree(root(t), t, PrintVisitor(names));

  treemap_slice_and_dice<vector_as_tree,box_min_max<float>,WeightMap>
    tmsd(t, wm);
  tmsd.visit(left_to_right, box_min_max<float>(0, 0, 1024,1024), root(t));
  return 0;
}
