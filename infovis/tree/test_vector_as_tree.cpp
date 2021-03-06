/* -*- C++ -*-
 *
 * Copyright (C) 2016 Jean-Daniel Fekete
 * 
 * This file is part of MillionVis.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
