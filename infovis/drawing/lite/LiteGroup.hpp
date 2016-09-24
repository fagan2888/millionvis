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
#ifndef INFOVIS_DRAWING_LITE_GROUP_HPP
#define INFOVIS_DRAWING_LITE_GROUP_HPP

#include <infovis/drawing/lite/LiteBounded.hpp>

namespace infovis {

/**
 * Lite that manages a list of sub-lites.
 */
class LiteGroup : public LiteBounded
{
public:
  LiteGroup();
  LiteGroup(const Box& b);
  virtual ~LiteGroup();

  virtual void setPosition(const Point& p);
  virtual Lite * clone() const;
  virtual int childCount() const;
  virtual Lite * getChild(int index) const;
  virtual void setChild(int index, Lite * l);
  virtual void addChild(Lite *);
  virtual void insertChild(int pos, Lite *);
  virtual void eraseChild(int pos);
  virtual iterator begin();
  virtual const_iterator begin() const;
  virtual iterator end();
  virtual const_iterator end() const;

  virtual bool isFixed() const;
  virtual void setFixed(bool f);
protected:
  virtual void computeBounds();
  List group_;
  bool is_fixed_;
};
  
} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_GROUP_HPP
