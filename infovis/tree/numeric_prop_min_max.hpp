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
#ifndef INFOVIS_TREE_NUMERIC_PROP_MIN_MAX_HPP
#define INFOVIS_TREE_NUMERIC_PROP_MIN_MAX_HPP

#include <infovis/tree/property_tree.hpp>
#include <limits>

namespace infovis {

inline void
numeric_prop_min_max(const property_tree::numeric_prop& prop,
		     float& min_value,
		     float& max_value)
{
  property_tree::numeric_prop::const_iterator i = prop.begin();
  if (i == prop.end()) {
    min_value = 0;
    max_value = 0;
    return;
  }
  min_value = max_value = *i++;

  while (i != prop.end()) {
    if (*i < min_value)
      min_value = *i;
    else if (*i > max_value)
      max_value = *i;
    i++;
  }
}

} // namespace infovis

#endif // INFOVIS_TREE_NUMERIC_PROP_MIN_MAX_HPP
