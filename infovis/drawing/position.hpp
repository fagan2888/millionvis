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
#ifndef INFOVIS_DRAWING_POSITION_HPP
#define INFOVIS_DRAWING_POSITION_HPP

#include <infovis/alloc.hpp>
#include <infovis/drawing/direction.hpp>

namespace infovis {

/**
 * Position data type
 */
enum position {
  pos_left,
  pos_bottom,
  pos_right,
  pos_top,
  pos_center
};

inline position default_position(direction d)
{
  switch(d) {
  case left_to_right:
    return pos_left;
  case right_to_left:
    return pos_right;
  case top_to_bottom:
    return pos_top;
  case bottom_to_top:
    return pos_bottom;
  }
  return pos_left;
}

inline position turn90(position d)
{
  switch(d) {
  case pos_left:
    return pos_bottom;
  case pos_bottom:
    return pos_right;
  case pos_right:
    return pos_top;
  case pos_top:
    return pos_left;
  case pos_center:
    return pos_center;
  }
}

inline position turn180(position d)
{
  switch(d) {
  case pos_left:
    return pos_right;
  case pos_bottom:
    return pos_top;
  case pos_right:
    return pos_left;
  case pos_top:
    return pos_bottom;
  case pos_center:
    return pos_center;
  }
}

};

#endif // INFOVIS_DRAWING_POSITION_HPP
