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
#ifndef INFOVIS_DRAWING_LITE_LAYOUT_HPP
#define INFOVIS_DRAWING_LITE_LAYOUT_HPP

#include <infovis/drawing/drawing.hpp>
#include <infovis/drawing/lite/Lite.hpp>
#include <vector>

namespace infovis {

/**
 * Base class for layout management
 */
class Layout : virtual public gc_cleanup
{
public:
  Layout() {}
  virtual ~Layout();

  virtual Layout * clone() const = 0;
  virtual void setLite(int i, Lite * l) = 0;
  virtual void addLite(Lite * lite) = 0;
  virtual void removeLite(Lite * lite) = 0;
  virtual void insertLite(int i, Lite * l) = 0;
  virtual void eraseLite(int i) = 0;
  virtual Box doLayoutIn(Lite * container) = 0;
};
  

} // namespace infovis 

#endif // INFOVIS_DRAWING_LITE_LAYOUT_HPP
