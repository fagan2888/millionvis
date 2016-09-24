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
#include <infovis/tree/xml_tree.hpp>
#include <infovis/tree/export_tree_xml.hpp>
#include <infovis/tree/sum_weight_visitor.hpp>
#include <iostream>

using namespace infovis;

int main(int argc, char * argv[])
{
  tree t;

  if (argc < 2) {
    std::cerr << "syntax: " << argv[0] << " <xml-file>\n";
    return 1;
  }
  std::cout << "Loading " << argv[1] << std::endl;
  xml_tree(argv[1], t);

  std::cout << "loaded\n";
  column * c = t.find_column("length");
  if (c != 0 && t.find_column("size") == 0) {
    c->set_name("size");
    FloatColumn * size = FloatColumn::cast(c);
    if (size != 0)
      sum_weights(t, *size);
  }

  std::cout << "exporting into dir.xml\n";
  export_tree_xml("dir.xml", t);
  return 0;
}
