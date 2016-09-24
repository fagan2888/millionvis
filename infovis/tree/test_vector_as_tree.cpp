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
#include <boost/directory.h>
#include <infovis/tree/visitor.hpp>
#include <iostream>

using namespace infovis;

struct PrintVisitor
{
  const std::vector<std::string,gc_alloc<std::string> >& names;
  int indent;

  PrintVisitor(const std::vector<std::string,gc_alloc<std::string> >& n)
    : names(n), indent(0) {}

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

static void build_tree(tree_traits< vector_as_tree >::node_descriptor parent,
		       vector_as_tree& tree, const std::string& dirname,
		       std::vector<std::string,gc_alloc<std::string> >& names)
{
  using namespace boost::filesystem;
  //std::cout << "entering " << dirname << std::endl;
  for (dir_it it(dirname); it != dir_it(); ++it) {
    if ((*it)[0] == '.')
      continue;
    tree_traits< vector_as_tree >::node_descriptor n = add_node(parent, tree);
    names.push_back(*it);
    if (boost::filesystem::get<is_directory>(it))
      build_tree(n, tree, dirname+"/"+(*it), names);
  }
  //std::cout << "leaving " << dirname << std::endl;
}

int main(int argc, char * argv[])
{
  std::vector<std::string,gc_alloc<std::string> > names;

  vector_as_tree t;
  add_node(root(t), t);

  if (argc == 1) {
    names.push_back(".");
    build_tree(root(t), t, ".", names);
  }
  else {
    names.push_back(argv[1]);
    build_tree(root(t), t, argv[1], names);
  }

  PrintVisitor vis(names);
  traverse_tree(root(t), t, vis);

  return 0;
}
