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
#include <infovis/tree/ObservableTree.hpp>

namespace infovis {

ObservableTree::ObservableTree()
{ }

tree::node_descriptor
ObservableTree::add_node(node_descriptor n)
{
  node_descriptor ret = tree::add_node(n);
  notifyBoundedRange();
  return ret;
}

void
ObservableTree::clear()
{
  tree::clear();
  notifyBoundedRange();
}

const BoundedRange *
ObservableTree::getBoundedRange() const 
{
  return this;
}

float 
ObservableTree::min() const
{
  return 0;
}

float 
ObservableTree::max() const
{
  return num_nodes();
}

float 
ObservableTree::value() const
{
  return num_nodes();
}

float 
ObservableTree::range() const
{
  return 0;
}

} // namespace infovis
