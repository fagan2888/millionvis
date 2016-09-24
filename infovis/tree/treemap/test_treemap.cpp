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
#include <infovis/tree/tree.hpp>
#include <infovis/tree/treemap/slice_and_dice.hpp>
#include <infovis/tree/treemap/squarified.hpp>
#include <boost/directory.h>
#include <infovis/drawing/direction_io.hpp>
#include <infovis/drawing/box_io.hpp>
#include <iostream>

using namespace infovis;

typedef FloatColumn WeightMap;

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
    wm.add(boost::filesystem::get<size>(it));
    if (boost::filesystem::get<is_directory>(it))
      build_tree(n, tree, dirname+"/"+(*it), names, wm);
  }
  //std::cout << "leaving " << dirname << std::endl;
}

static inline void
tab(int depth) { while(depth--) std::cout << ' '; }

template <class Tree, class Box>
struct print_drawer : public null_drawer<Tree,Box> {
  void begin_strip(const Box& b,
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth,
		   direction dir) {
    tab(depth);
    std::cout << "begin_strip " << b << ", dir=" << dir << std::endl;
  }
  void end_strip(const Box& b,
		 typename tree_traits<Tree>::node_descriptor n,
		 unsigned depth,
		 direction dir) {
    tab(depth);
    std::cout << "end_strip " << b << ", dir=" << dir << std::endl;
  }

#if 0
  bool begin_box(const Box& b,
		 typename tree_traits<Tree>::node_descriptor n,
		 unsigned depth) {
    tab(depth);
    std::cout << "begin_" << b << std::endl;
    return true;
  }
#endif
  void draw_box(const Box& b,
		typename tree_traits<Tree>::node_descriptor n,
		unsigned depth) {
    tab(depth);
    std::cout << "node " <<  n << " draw_" << b << std::endl;
  }
#if 0
  void draw_border(Box& b, 
		   typename tree_traits<Tree>::node_descriptor n,
		   unsigned depth) {
    tab(depth);
    std::cout << "border_" << b << std::endl;
  }
  void end_box(const Box& b, 
	       typename tree_traits<Tree>::node_descriptor n,
	       unsigned depth) {
    tab(depth);
    std::cout << "end_" << b << std::endl;
  }
#endif
};

int main(int argc, char * argv[])
{
  typedef box_min_max<float> Box;
  typedef vector_as_tree Tree;
  std::vector<std::string,gc_alloc<std::string> > names;
  WeightMap * wm;

  Tree t;

  if (argc == 1) {
    names.push_back(".");
    build_tree(root(t), t, ".", names, wm);
  }
  else {
    names.push_back(argv[1]);
    build_tree(root(t), t, argv[1], names, wm);
  }
  
  sum_weights(t, wm);
  PrintVisitor vis(names, wm);
  traverse_tree(root(t), t, vis);

  treemap_squarified<
    Tree,
    Box,
    WeightMap&,
    print_drawer<Tree,Box>
    > tms(t, wm);
  tms.start();
  tms.visit(Box(0, 0, 1024,1024), root(t));
  tms.finish();
  return 0;
}
