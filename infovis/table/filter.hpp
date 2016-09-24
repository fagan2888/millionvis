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
#ifndef INFOVIS_TABLE_FILTER_HPP
#define INFOVIS_TABLE_FILTER_HPP

#include <infovis/alloc.hpp>
#include <infovis/table/column.hpp>

namespace infovis {

//typedef CharColumn FilterColumn;

/**
 * Filter class to filter out elements in some algorithms.
 */
struct filter_none {
  template <class N>
  bool operator() (N) const { return false; }
};

template <class T>
struct filter_column_of
{
  bool operator()(const T& val) const {
    return false;
  }
};

template <class T>
struct filter_range_column_of
{
  T min_;
  T max_;

  filter_range_column_of(const T& min, const T& max)
    : min_(min), max_(max)
  { }
  bool operator()(const T& val) const {
    return min_ <= val && val <= max_;
  }
};

template <class T, class Filter>
struct filter_update_min_max
{
  T min_;
  T max_;
  bool valid_;
  Filter filter_;

  filter_update_min_max(Filter filter)
    : valid_(false), filter_(filter)
  { }
  bool operator()(const T& val) {
    if (filter(val))
      return true;
    if (! valid_) {
      min_ = max_ = val;
      valid_ = true;
    }
    else if (val < min_)
      min_ = val;
    else if (val > max_)
      max_ = val;
    return false;
  }
};

#if 0
template <class T, class Filter>
inline void
filter_column(FilterColumn& filter_col,
	      const column_of<T>& col,
	      Filter filter)
{
  int end = col.size();
  for (int i = 0; i < end; i++) {
    filter_col &&= filter(col[i]);
  }
}
#endif

} // namespace infovis

#endif // INFOVIS_TABLE_FILTER_HPP

