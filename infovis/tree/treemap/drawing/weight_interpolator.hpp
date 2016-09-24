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
#ifndef INFOVIS_TREE_TREEMAP_DRAWING_WEIGHT_INTERPOLATOR_HPP
#define INFOVIS_TREE_TREEMAP_DRAWING_WEIGHT_INTERPOLATOR_HPP

#include <vector>
#ifndef NDEBUG
#include <cassert>
#include <cfloat>
#include <iostream>
#endif

namespace infovis {

/**
 * Interpolates between two columns.
 */
template <class DAContainer>
struct weight_interpolator
{
  typedef typename DAContainer::value_type value_type;

  const DAContainer* from;
  const DAContainer* to;
  float param;
  float balance;

  weight_interpolator(const DAContainer& f, const DAContainer& t)
    : from(&f), to(&t), param(0), balance(1) {}

  weight_interpolator(const weight_interpolator& other)
    : from(other.from),
      to(other.to),
      param(other.param),
      balance(other.balance) { }

  weight_interpolator& operator = (const weight_interpolator& other) {
    from = other.from;
    to = other.to;
    param = other.param;
    balance = other.balance;
    return *this;
  }
  void set_param(float p) { param = p; }
  float get_param() const { return param; }
  void set_balance(float b) { balance = b; }
  float get_balance() const { return balance; }
  void set_std_balance() { balance = (*from)[0] / (*to)[0]; }

  value_type operator[](int i) const {
    float f = (*from)[i];
    float t = (*to)[i];
    float ret =
      (1.0f - param) * f + param * t * balance;
#if 0
    if (_isnan(ret)) {
      std::cerr << "nan found at index " << i << std::endl;
      return 0.0f;
    }
#endif
    return ret;
  }
};

template <class T>
inline typename weight_interpolator<T>::value_type
get(const weight_interpolator<T>& pa, int k) { return pa[k]; }

} // namespace infovis

#endif // INFOVIS_TREE_TREEMAP_DRAWING_WEIGHT_INTERPOLATOR_HPP
