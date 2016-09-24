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
#ifndef INFOVIS_DRAWING_DIRECTION_IO_HPP
#define INFOVIS_DRAWING_DIRECTION_IO_HPP

#include <infovis/drawing/direction.hpp>
#include <iostream>

namespace infovis {

inline const char * to_string(direction d)
{
  switch(d) {
  case left_to_right:
    return "left_to_right";
    break;
  case right_to_left:
    return "right_to_left";
    break;
  case top_to_bottom:
    return "top_to_bottom";
    break;
  case bottom_to_top:
    return "bottom_to_top";
    break;
  }
  return "";
}


inline std::ostream& operator << (std::ostream& out, direction d)
{
  return out << to_string(d);
}

}

#endif // INFOVIS_DRAWING_DIRECTION_IO_HPP
