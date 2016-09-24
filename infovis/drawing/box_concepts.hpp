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
#ifndef INFOVIS_DRAWING_BOX_CONCEPTS_HPP
#define INFOVIS_DRAWING_BOX_CONCEPTS_HPP

#include <boost/concept_check.hpp>
#include <infovis/drawing/box.hpp>

namespace infovis {

/**
 * Box Concept (Abstract requirements for a box).
 */
template <class Box>
struct BoxConcept
{
  typedef typename box_traits<Box>::coord_type coord_type;
  typedef typename box_traits<Box>::dist_type dist_type;
  typedef typename box_traits<Box>::point_type point_type;
  typedef typename box_traits<Box>::vector_type vector_type;

  void constraints() {
    boost::function_requires< boost::EqualityComparableConcept<coord_type> >();
    boost::function_requires< boost::ComparableConcept<coord_type> >();
    boost::function_requires< boost::AssignableConcept<coord_type> >();

    x = xmin(b);
    y = ymin(b);
    x = xmax(b);
    y = ymax(b);
    u = width(b);
    v = height(b);
    pt = min(b);
    pt = max(b);
    vec = extent(b);
    x = set_xmin(b, x);
    y = set_ymin(b, y);
    x = set_xmax(b, x);
    y = set_ymax(b, y);
    u = set_width(b, u);
    v = set_height(b, v);
    pt = set_min(b, pt);
    pt = set_max(b, pt);
    vec = set_extent(b, vec);
    translate(b, u, v);
    translate(b, vec);
    add_point(b, x, y);
    const_constraints(b);
  }
  void const_constraints(const Box&  b) {
    coord_type x, y;
    dist_type u, v;
    point_type pt;
    vector_type vec;

    x = xmin(b);
    y = ymin(b);
    x = xmax(b);
    y = ymax(b);
    u = width(b);
    v = height(b);
    pt = min(b);
    pt = max(b);
    vec = extent(b);
    bool bv = inside(b, x, y);
    bv = intersects(b, b);
    bv = contains(b, b);
    bv = empty(b);
  }

  coord_type x, y;
  dist_type u, v;
  point_type pt;
  vector_type vec;
  Box b;
};

} // namespace infovis

#endif
