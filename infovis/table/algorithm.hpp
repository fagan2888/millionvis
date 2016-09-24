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
#ifndef INFOVIS_TABLE_ALGORITHM_HPP
#define INFOVIS_TABLE_ALGORITHM_HPP

#include <infovis/alloc.hpp>
#include <infovis/table/column.hpp>
#include <set>

namespace infovis {

template <class T>
inline void column_element_set(const column_of<T>& col, std::set<T>& elems)
{
  for (column_of<T>::const_iterator i = col.begin();
       i != col.end(); i++) {
    elems.insert(*i);
  }
}

template <class T>
inline void
column_element_count(const column_of<T>& col)
{
  std::set<T> elems;
  column_element_set(col, elems);

  return elems.size();
}

} // namespace infovis

#endif // INFOVIS_TABLE_ALGORITHM_HPP
