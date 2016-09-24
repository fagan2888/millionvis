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
#ifdef VECTOR_AS_TREE
#include <infovis/tree/vector_as_tree.hpp>
#include <infovis/tree/dir_property_tree.hpp>
#include <infovis/tree/xml_property_tree.hpp>
#else
#include <infovis/tree/tree.hpp>
#include <infovis/tree/dir_tree.hpp>
#include <infovis/tree/xml_tree.hpp>
#endif
#include <infovis/tree/sum_weight_visitor.hpp>
#include <iostream>

using namespace infovis;

int main(int argc, char * argv[])
{
  int i;
#ifdef VECTOR_AS_TREE
  std::vector<float, gc_alloc<float,true> > wm;
  std::vector<float, gc_alloc<float,true> > swm;
  vector_as_tree t;

  if (argc == 1) {
    dir_property_tree(".", tree);
  }
  else {
    if (xml_property_tree(argv[1], tree) == 1) {
      dir_property_tree(argv[1], tree);
    }
  }
  
  //sum_weight_visitor<vector_as_tree,std::vector<float,gc_alloc<float,true> > > vis(t, wm, swm);
#else
  tree t;

  if (argc == 1) {
    dir_tree(".", t);
  }
  else {
    if (xml_tree(argv[1], t) == 1) {
      dir_tree(argv[1], t);
    }
  }

  FloatColumn * wm = 0;
  for (i = 0; i < t.column_count(); i++) {
    wm = FloatColumn::cast(t.get_column(i));
    if (wm != 0)
      break;
  }
  if (wm == 0) {
    std::cerr << "Cannot find a float column\n";
    return 1;
  }
#endif

  //traverse_tree(root(t), t, vis);
  sum_weights(t, *wm);
  //swm = sum_weights(tree, wm);
  for (i = 0; i < wm->size(); i++) {
    std::cout << "sum[" << i << "] = " << wm->get_value(i) << std::endl;
  }
  
  return 0;
}
