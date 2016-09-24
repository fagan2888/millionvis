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
#ifndef TREEMAP2_TYPES_HPP
#define TREEMAP2_TYPES_HPP

#include <infovis/drawing/lite/Lite.hpp>
#include <infovis/tree/ObservableTree.hpp>
//#include <infovis/table/filter.hpp>
#include <vector>

namespace infovis {

//typedef tree Tree;
typedef ObservableTree Tree;

typedef FloatColumn WeightMap;
typedef UnsignedColumn FilterColumn;

inline unsigned
node_depth(unsigned n, const Tree& t)
{
  unsigned depth = 0;
  if (n == root(t))
    return 0;
  while (n != root(t)) {
    depth++;
    n = parent(n, t);
  }
  return depth;
}

typedef tree_traits<Tree>::node_descriptor node_descriptor;
typedef Lite::Path Path;
typedef std::vector<Box> PathBoxes;

inline string
subprop(const string& sub, const string& name)
{
  return name + "_" + sub;
}

inline bool
has_subprop(const string& sub, const string& name)
{
  int i;
  if (name.length() < (sub.length()+1))
    return false;
  for (i = 0; i < sub.length(); i++) {
    if (sub[sub.length()-1-i] != name[name.length()-1-i])
      return 0;
  }
  return name[name.length()-1-i] == '_';
}

} // namespace infovis

#endif // TREEMAP2_TYPES_HPP
