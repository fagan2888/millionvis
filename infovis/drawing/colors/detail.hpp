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
#ifndef INFOVIS_DRAWING_COLORS_DETAILS_HPP
#define INFOVIS_DRAWING_COLORS_DETAILS_HPP

#include <limits>

namespace infovis {

namespace detail {
template <class T>
inline T one(const T&, int&)
{
  return std::numeric_limits<T>::max();
}

template <class T>
inline T one(const T&, float&)
{
  return T(1);
}

template <class T>
inline T one(const T& t)
{
  typename boost::detail::if_true<(std::numeric_limits<T>::is_integer)>
    ::template then<int,float>::type int_or_float;
  return one(t, int_or_float);
}


template <class S, class T>
inline void convert(S& s, int, const T& t, int)
{
  s = t * one(s) / one(t);
}

template <class S, class T>
inline void convert(S& s, float, const T& t, int)
{
  s = S(t / S(one(t)));
}

template <class S, class T>
inline void convert(S& s, int, const T& t, float)
{
  s = S(t * one(s));
}

template <class S, class T>
inline void convert(S& s, float&, const T& t, float)
{
  s = t;
}

template <class S, class T>
inline void convert(S& s, const T& t)
{
  typename boost::detail::if_true<(std::numeric_limits<S>::is_integer)>
    ::template then<int,float>::type int_or_float1(0);
  typename boost::detail::if_true<(std::numeric_limits<T>::is_integer)>
    ::template then<int,float>::type int_or_float2(0);
  convert(s, int_or_float1, t, int_or_float2);
}

inline void round(double& v, double d) { v = d; }
inline void round(float& v, double d) { v = float(d); }
inline void round(unsigned long& v, double d) { v = (unsigned long)(d + 0.5); }
inline void round(long& v, double d) { v = long(d + 0.5); }
inline void round(unsigned int& v, double d) { v = (unsigned int)(d + 0.5); }
inline void round(int& v, double d) { v = int(d + 0.5); }
inline void round(unsigned short& v, double d) { v = (unsigned short)(d + 0.5); }
inline void round(short& v, double d) { v = short(d + 0.5); }
inline void round(unsigned char& v, double d) { v = (unsigned char)(d + 0.5); }
inline void round(char& v, double d) { v = char(d + 0.5); }

} // namespace detail

} // namespace infovis

#endif
