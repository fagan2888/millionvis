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
#ifndef INFOVIS_DRAWING_LITE_LAYOUTBOX_HPP
#define INFOVIS_DRAWING_LITE_LAYOUTBOX_HPP

#include <infovis/drawing/drawing.hpp>
#include <infovis/drawing/lite/Lite.hpp>
#include <infovis/drawing/lite/LayoutStack.hpp>

namespace infovis {

/**
 * Layout Lites in a given direction.
 */
class LayoutBox : public LayoutStack
{
public:
  enum Direction {
    horizontal,
    vertical
  };
  LayoutBox(Direction dir = vertical, float gap = 0);
  ~LayoutBox();

  virtual Layout * clone() const;

  virtual Box doLayoutIn(Lite * container);

  Direction getDirection() const {return dir_; }
  void setDirection(Direction v) {dir_ = v; }
  
protected:
  Direction dir_;
  float gap_;
};

} // namespace infovis 

#endif // INFOVIS_DRAWING_LITE_LAYOUTBOX_HPP
