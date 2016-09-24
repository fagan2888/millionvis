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
#include <infovis/tree/property_tree.hpp>
#include <infovis/tree/visitor.hpp>
#include <infovis/tree/dir_property_tree.hpp>
#include <infovis/tree/xml_property_tree.hpp>
#include <iostream>

using namespace infovis;

typedef property_tree Tree;
typedef tree_traits<Tree>::node_descriptor node_descriptor;
typedef Tree::prop_id prop_id;

struct PrintVisitor
{
  const Tree& tree;
  unsigned indent;

  PrintVisitor(const Tree& t)
    : tree(t),
      indent(0)
  {}

  static void tab(int i) {
    while (i-- != 0)
      std::cout << ' ';
  }
  void preorder(node_descriptor n) {
    tab(indent++);
    for (Tree::names_iterator name = tree.begin_names();
	 name != tree.end_names(); name++) {
      tab(indent);
      std::cout << ": " << *name << " = ";
      Tree::prop_id id = tree.get_prop_id(*name);
      if (id.is_numeric()) {
	std::cout << tree.get_prop_numeric(id)[n] << std::endl;
      }
      else {
	std::cout << tree.get_prop_string(id)[n] << std::endl;
      }
    }
  }
  void inorder(node_descriptor n) {
  }
  void postorder(node_descriptor n) {
    indent--;
  }
};

int main(int argc, char * argv[])
{
  Tree tree;

  prop_id names = tree.add_property("name", property_tree::type_string);
  prop_id sizes = tree.add_property("size", property_tree::type_numeric);

  if (argc == 1) {
    dir_property_tree(".", tree);
  }
  else {
    if (xml_property_tree(argv[1], tree) == 1) {
      dir_property_tree(argv[1], tree);
    }
  }

  PrintVisitor vis(tree);
  traverse_tree(root(tree), tree, vis);

  return 0;
}
