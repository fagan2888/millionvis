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
#ifndef INFOVIS_DRAWING_DIRECTION_HPP
#define INFOVIS_DRAWING_DIRECTION_HPP

#include <infovis/alloc.hpp>

namespace infovis {

/**
 * direction data type holding four possible directions.
 */
enum direction {
  left_to_right,
  right_to_left,
  top_to_bottom,
  bottom_to_top
};

inline direction flip(direction d)
{
  switch(d) {
  case left_to_right:
    return top_to_bottom;
  case right_to_left:
    return bottom_to_top;
  case top_to_bottom:
    return left_to_right;
  case bottom_to_top:
    return right_to_left;
  }
  return left_to_right;
}
  
inline direction turn90(direction d)
{
  switch(d) {
  case left_to_right:
    return top_to_bottom;
  case right_to_left:
    return bottom_to_top;
  case top_to_bottom:
    return right_to_left;
  case bottom_to_top:
    return left_to_right;
  }
}
inline direction turn180(direction d)
{
  switch(d) {
  case left_to_right:
    return right_to_left;
  case right_to_left:
    return left_to_right;
  case top_to_bottom:
    return bottom_to_top;
  case bottom_to_top:
    return top_to_bottom;
  }
  return right_to_left;
}

};

#endif // INFOVIS_DRAWING_DIRECTION_HPP
