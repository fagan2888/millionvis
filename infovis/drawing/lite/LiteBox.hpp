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
#ifndef INFOVIS_DRAWING_LITEBOX_HPP
#define INFOVIS_DRAWING_LITEBOX_HPP

#include <infovis/drawing/lite/LiteGroup.hpp>
#include <infovis/drawing/lite/LayoutBox.hpp>

namespace infovis {

/**
 * Base class for objec doing layout management.
 */
class LiteBox : public LiteGroup
{
public:
  LiteBox(Layout * l = new LayoutBox);

  virtual Lite * clone() const;

  virtual void setChild(int index, Lite *);
  virtual void addChild(Lite *);
  virtual void removeChild(Lite *);
  virtual void insertChild(int pos, Lite *);
  virtual void eraseChild(int pos);
  virtual void pack();

  virtual Layout * getLayout() const;
  virtual void setLayout(Layout * v);
  

protected:
  
  virtual void computeBounds();
  Layout * layout_;
};

} // namespace infovis


#endif // INFOVIS_DRAWING_LITEBOX_HPP
