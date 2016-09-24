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
#ifndef INFOVIS_TREE_OBSERVABLETREE_HPP
#define INFOVIS_TREE_OBSERVABLETREE_HPP

#include <infovis/tree/tree.hpp>
#include <infovis/drawing/notifiers/BoundedRange.hpp>

namespace infovis {

class ObservableTree : public tree,
		       public AbstractBoundedRangeObservable,
		       public BoundedRange
{
public:
  ObservableTree();

  virtual node_descriptor add_node(node_descriptor n);
  virtual void clear();

  virtual const BoundedRange * getBoundedRange() const;

  virtual float min() const;
  virtual float max() const;
  virtual float value() const;
  virtual float range() const;
};

template<>
struct tree_traits<ObservableTree> : public ObservableTree {
};

} // namespace infovis

#endif // INFOVIS_TREE_OBSERVABLETREE_HPP
